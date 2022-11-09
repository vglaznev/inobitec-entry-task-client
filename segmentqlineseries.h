#ifndef SEGMENTQLINESERIES_H
#define SEGMENTQLINESERIES_H

#include <QObject>
#include <QHash>
#include <QVector>

namespace QtCharts {
	class QChart;
	class QValueAxis;
	class QLineSeries;
};


class SegmentQLineSeries : public QObject
{
	Q_OBJECT

public:
	explicit SegmentQLineSeries(QtCharts::QChart*, QtCharts::QValueAxis*, QtCharts::QValueAxis*);
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
	QtCharts::QChart* chart;
	QtCharts::QValueAxis* xAxis;
	QtCharts::QValueAxis* yAxis;

	QHash<SegmentType, QColor> segmentTypeColor;
	int width;

	QVector<QtCharts::QLineSeries*> segments;
	int numberOfPoints;

	QHash<SegmentType, QVector<int>> segmentTypeIndexes;

	SegmentType lastSegmentType;
};

#endif

