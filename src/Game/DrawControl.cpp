#include "DrawControl.hpp"

namespace game
{
void DrawControl::startDraw()
{
	if (!m_isDrawing)
	{
		std::cout << "draw" << std::endl;
		m_isDrawing = true;
	}
}

void DrawControl::stopDraw()
{
	if (m_isDrawing)
	{
		std::cout << "stop draw" << std::endl;
		if (m_points.size() < m_MIN_POINTS || !evaluateData())
		{
			//todo: failed evaluation
		}
		m_points.clear();
		m_isDrawing = false;
	}
}

void DrawControl::addPoint(const sf::Vector2f& pos)
{
	if (m_isDrawing)
	{
		m_points.push_back(pos);
	}
}

void DrawControl::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (m_isDrawing)
	{
		for (auto i : m_points)
		{
			m_dot.setPosition(i);
			target.draw(m_dot, states);
		}
	}
}

bool DrawControl::evaluateData() const
{
	const size_t count = m_points.size();
	if (count == 0)
	{
		return false;
	}

	// means
	float sumX = 0.f;
	float sumY = 0.f;
	for (const auto& i : m_points)
	{
		sumX += i.x;
		sumY += i.y;
	}
	const float meanX = sumX / count;
	const float meanY = sumY / count;

	//slope
	float numerator = 0.0f;
	float denominator = 0.0f;

	for (const auto& i : m_points)
	{
		float xOff = i.x - meanX;
		numerator += xOff * (i.y - meanY);
		denominator += xOff * xOff;
	}

	float m, b, err = 0.f;
	if (denominator == 0.f)
	{ // vertical
		m = 1.f;
		b = 0;
		for (const auto& i : m_points)
		{
			float t = (i.x - meanX);
			float perpDist = (t * t); // perp dist to line squared
			err += perpDist;
		}
	}
	else if (numerator == 0.f)
	{ // horizontal
		m = 0.f;
		b = meanY;
		for (const auto& i : m_points)
		{
			float t = (i.y - meanY);
			float perpDist = (t * t); // perp dist to line squared
			err += perpDist;
		}
	}
	else
	{
		m = numerator / denominator; // y=mx+b
		b = meanY - m * meanX;

		// err
		err = 0;
		for (const auto& i : m_points)
		{
			float t = (i.y - (m * i.x + b));
			float perpDist = (t * t) / (1 + m * m); // perp dist to line squared
			err += perpDist;
		}
	}

	const float meanErr = err / count;
	std::cout << meanErr << std::endl; // temp

	// endpoints
	sf::Vector2f first = m_points.front();
	first.y -= b;
	const float sCoef = (first.x * denominator + first.y * numerator) / (numerator * numerator + denominator * denominator);
	sf::Vector2f startPoint = sf::Vector2f(sCoef * denominator, sCoef * numerator + b);

	sf::Vector2f last = m_points.back();
	last.y -= b;
	const float eCoef = (last.x * denominator + last.y * numerator) / (numerator * numerator + denominator * denominator);
	sf::Vector2f endPoint = sf::Vector2f(eCoef * denominator, eCoef * numerator + b);

	const float MAX_LINE_ERR = 20.f;
	if (meanErr > MAX_LINE_ERR)
	{
		sf::Vector2f fr = m_points.front();
		sf::Vector2f bk = m_points.back();

		return evaluateSine(bk.y-fr.y, bk.x-fr.x, startPoint, startPoint, endPoint);
		//return evaluateSine(numerator, denominator, b, startPoint, endPoint);
	}
	else
	{
		return evaluateLine(startPoint, endPoint, meanErr);
	}
}

bool DrawControl::evaluateLine(const sf::Vector2f& startPoint, const sf::Vector2f& endPoint, float meanErr) const
{
	// health
	float health = 0;
	float length = v2fDist(startPoint, endPoint);
	if (meanErr > 0.f)
	{
		health = 1 / meanErr * length;
	}
	else
	{
		health = length;
	}

	// make Boundary //todo: fix team number
	Boundary bound(sf::Uint8(1U), health, startPoint, endPoint);
	m_actors->m_boundaryPool.add(bound);
	return true;
}

bool DrawControl::evaluateSine(float mRise, float mRun, const sf::Vector2f& origin, const sf::Vector2f& startPoint, const sf::Vector2f& endPoint) const
{
	using namespace std;

	// shift and rotate axis using linear fit
	float mHypot = sqrtf(mRise * mRise + mRun * mRun);
	float sinTheta = mRise / mHypot;
	float cosTheta = mRun / mHypot;
	vector<float> xRot;
	vector<float> yRot;
	for (const auto& i : m_points)
	{
		xRot.push_back((i.x - origin.x) * cosTheta - (i.y - origin.y) * sinTheta);
		yRot.push_back((i.x - origin.x) * sinTheta + (i.y - origin.y) * cosTheta);
	}

	// ascending sort
	// https://stackoverflow.com/a/12399290
	vector<size_t> idx(xRot.size());
	iota(idx.begin(), idx.end(), 0);
	stable_sort(idx.begin(), idx.end(), [&xRot](size_t i1, size_t i2) { return xRot[i1] < xRot[i2]; });
	// end stackoverflow

	// sort by ascending x-value and shift to start at x=0
	vector<float> xRotSort;
	vector<float> yRotSort;
	size_t xRotMin = idx[0];
	for (auto i : idx)
	{
		xRotSort.push_back(xRot[i] - xRot[xRotMin]);
		yRotSort.push_back(yRot[i] - yRot[xRotMin]);
	}

	// make fixed spacing axis
	const int PIXELS_PER_TICK = 1;
	size_t nTicks = floor(xRotSort.back() / PIXELS_PER_TICK) + 1;
	// interpolate
	vector<float> dataIn(nTicks);
	size_t k { 0U }, l { 1U };
	for (size_t i = 0U; i < dataIn.size(); i++)
	{
		float x = i * PIXELS_PER_TICK;
		while (x > xRotSort.at(l))
		{
			k++;
			l++;
		}
		//interp
		dataIn[i] = yRotSort[k] + (x - xRotSort[k]) * (yRotSort[l] - yRotSort[k]) / (xRotSort[l] - xRotSort[k]);
	}

	// fft
	using namespace pocketfft;

	shape_t shapeIn { dataIn.size() }, shapeOut { dataIn.size() / 2 + 1 };
	stride_t strideIn(shapeIn.size()), strideOut(shapeOut.size());
	strideIn[0] = sizeof(float);
	strideOut[0] = sizeof(complex<float>);

	vector<complex<float>> dataOut(shapeOut[0]);
	const float M_PI_f = (float)M_PI;

	size_t axis = 0U;
	r2c(shapeIn, strideIn, strideOut, axis, FORWARD, dataIn.data(), dataOut.data(), 1.f / 2.f / M_PI_f);

	float max = 0.f;
	float maxPhase = 0.f;
	size_t maxIdx = -1;
	for (size_t i = 0; i < dataOut.size(); i++)
	{
		float l = abs(dataOut.at(i));
		if (l > max && i != 0)
		{
			max = l;
			maxIdx = i;
			maxPhase = arg(dataOut.at(i));
		}
	}
	printf("Mag of max: %f\n", max);
	printf("Phase of max: %f\n", maxPhase);
	printf("Idx of max: %zu\n", maxIdx);
	if (startPoint == endPoint) // temp
	{
	}

	// todo: team, health, amplitude, speed,
	float rms = 0.f;
	for (auto i : yRotSort)
	{
		rms += i * i;
	}
	rms /= yRotSort.size();
	rms = sqrtf(rms);

	float health = 100.f;
	float frequency = 2.f * M_PI_f * static_cast<float>(maxIdx) / (nTicks * PIXELS_PER_TICK);
	float amplitude = rms * 1.41421356237; // sqrt 2
	float speed = 5.f;

	Ray newRay(sf::Uint8(1U), health, startPoint, endPoint, frequency, amplitude, speed);
	m_actors->m_rayPool.add(newRay);
	return true;
}

}