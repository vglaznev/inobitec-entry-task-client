#ifndef SEGMENTQLINESERIES_H
#define SEGMENTQLINESERIES_H

#include <QObject>
#include <QHash>
#include <QQueue>
#include <memory>

namespace QtCharts {
	class QChart;
	class QValueAxis;
	class QLineSeries;
};


class SegmentQLineSeries : public QObject
{
	Q_OBJECT

public:
	explicit SegmentQLineSeries(QObject* parent = nullptr, int _maxNumberOfPoints = 2000, int _maxNumberOfSegments = 15);
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

signals:

	void newSegmentAppend(QtCharts::QLineSeries*);
	void segmentRemoved(QtCharts::QLineSeries*);

private:
	const int maxNumberOfPoints;
	const int maxNumberOfSegments;

	QHash<SegmentType, QColor> segmentTypeColor;
	int width;

	QHash<SegmentType, QQueue<QtCharts::QLineSeries*>> segments;
	int numberOfPoints;


	SegmentType lastSegmentType;
	SegmentType firstSegmentType;

	void removeFirstSegment();
	void cleanPointsOnOverFlow();
};

#endif

