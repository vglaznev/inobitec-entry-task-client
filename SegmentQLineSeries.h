#ifndef SEGMENTQLINESERIES_H
#define SEGMENTQLINESERIES_H

#include <QObject>
#include <QMap>
#include <QVector>

class QChart;
class QValueAxis;
class QLineSeries;

class SegmentQLineSeries : public QObject
{
	Q_OBJECT

public:
	explicit SegmentQLineSeries(QChart*, QValueAxis*, QValueAxis*);
	~SegmentQLineSeries();

	void append(QPointF);
	void clear();

	enum SegmentType;

	void setColor(QColor, SegmentType);
	void setWidth(int);

	int size();

	QPointF getLastPoint();

	enum SegmentType {
		INCREASING,
		DECREASING
	};

private:
	QChart* chart;
	QValueAxis* xAxis;
	QValueAxis* yAxis;

	/*QColor increasingSegmentColor;
	QColor decreasingSegmentColor;*/
	QMap<SegmentType, QColor> segmentTypeColor;
	int width;

	QVector<QLineSeries*> segments;
	int numberOfPoints;

	/*QVector<int> indexOfDecreasingSegments;
	QVector<int> indexOfIncreasingSegments;*/
	QMap<SegmentType, QVector<int>> segmentTypeIndexes;

	SegmentType lastSegmentType;
};

#endif

