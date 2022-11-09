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
	explicit SegmentQLineSeries(QObject* parent = nullptr);
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

private:
	QHash<SegmentType, QColor> segmentTypeColor;
	int width;

	QVector<QtCharts::QLineSeries*> segments;
	int numberOfPoints;

	QHash<SegmentType, QVector<int>> segmentTypeIndexes;

	SegmentType lastSegmentType;
};

#endif

