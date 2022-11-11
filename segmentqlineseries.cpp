#include "segmentqlineseries.h"

#include <QChart>
#include <QValueAxis>
#include <QLineSeries>
#include <QDebug>

using QtCharts::QChart;
using QtCharts::QLineSeries;
using QtCharts::QValueAxis;

SegmentQLineSeries::SegmentQLineSeries(QObject* parent, int _maxNumberOfPoints, int _maxNumberOfSegments) :
	QObject(parent),
	maxNumberOfPoints(_maxNumberOfPoints),
	maxNumberOfSegments(_maxNumberOfSegments),
	numberOfPoints(0),
	width(1),
	firstSegmentType(DECREASING),
	lastSegmentType(INCREASING)
{
	segmentTypeColor.insert(INCREASING, Qt::red);
	segmentTypeColor.insert(DECREASING, Qt::blue);

	segments.insert(INCREASING, QQueue<QtCharts::QLineSeries*>());
	segments.insert(DECREASING, QQueue<QtCharts::QLineSeries*>());
}

SegmentQLineSeries::~SegmentQLineSeries() {
}

void SegmentQLineSeries::append(QPointF point) {
	QLineSeries* lastSegment;
	QLineSeries* currentSegment;
	SegmentType currentSegmentType = DECREASING;
	
	if (numberOfPoints != 0) {
		lastSegment = segments[lastSegmentType].last();
		QPointF lastPointInSeries = lastSegment->at(lastSegment->count() - 1);
		currentSegmentType = point.y() <= lastPointInSeries.y() ? DECREASING : INCREASING;
	}
	
	if (currentSegmentType != lastSegmentType) {
		currentSegment = new QLineSeries(this);
		
		segments[currentSegmentType].enqueue(currentSegment);

		QPen pen;
		pen.setColor(segmentTypeColor[currentSegmentType]);
		pen.setWidth(width);
		currentSegment->setPen(pen);

		lastSegmentType = currentSegmentType;

		emit newSegmentAppend(currentSegment);
	}
	else {
		currentSegment = lastSegment;
	}

	currentSegment->append(point);
	numberOfPoints++;

	
}

void SegmentQLineSeries::clear() {
	firstSegmentType = DECREASING;
	lastSegmentType = INCREASING;
	numberOfPoints = 0;
	segments[INCREASING].clear();
	segments[DECREASING].clear();
}

void SegmentQLineSeries::setWidth(int _width) {
	width = _width;

	if (numberOfPoints == 0) {
		return;
	}

	if (!segments[INCREASING].isEmpty()) {

		QPen pen = segments[INCREASING][0]->pen();
		pen.setWidth(width);

		for (const auto& segment : segments[INCREASING]) {
			segment->setPen(pen);
		}
	}

	if (!segments[DECREASING].isEmpty()) {

		QPen pen = segments[DECREASING][0]->pen();
		pen.setWidth(width);

		for (const auto& segment : segments[DECREASING]) {
			segment->setPen(pen);
		}
	}
}

void SegmentQLineSeries::setColor(QColor color, SegmentType segmentType) {

	const QQueue<QtCharts::QLineSeries*> segmentsOfSpecificType = segments[segmentType];
	segmentTypeColor[segmentType] = color;
	
	if (segmentsOfSpecificType.size() != 0) {

		QPen pen = segmentsOfSpecificType[0]->pen();
		pen.setColor(color);

		for (const auto& segment : segmentsOfSpecificType) {
			segment->setPen(pen);
		}
	}
}

QPointF SegmentQLineSeries::getLastPoint() {
	QLineSeries* lastSegment = segments[lastSegmentType].last();
	return lastSegment->at(lastSegment->count() - 1);
}

int SegmentQLineSeries::size() {
	return numberOfPoints;
}

void SegmentQLineSeries::removeFirstSegment() {
	numberOfPoints -= segments[firstSegmentType].head()->count();
	emit segmentRemoved(segments[firstSegmentType].dequeue());
	firstSegmentType = (firstSegmentType == INCREASING ? DECREASING : INCREASING);
}

void SegmentQLineSeries::cleanPointsOnOverFlow() {
	if (segments[INCREASING].size() + segments[DECREASING].size() > maxNumberOfSegments) {
		removeFirstSegment();
	}
	while (numberOfPoints - segments[firstSegmentType].head()->count() > maxNumberOfPoints) {
		removeFirstSegment();
	}
	if (numberOfPoints > maxNumberOfPoints) {
		QLineSeries* firstSegment = segments[firstSegmentType].head();
		firstSegment->replace(firstSegment->points().mid(numberOfPoints - maxNumberOfPoints / 2, numberOfPoints));
		numberOfPoints = maxNumberOfPoints / 2;
	}
}