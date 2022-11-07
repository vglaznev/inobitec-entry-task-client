#include "SegmentQLineSeries.h"

#include <QChart>
#include <QValueAxis>
#include <QLineSeries>
#include <QDebug>

using QtCharts::QChart;
using QtCharts::QLineSeries;
using QtCharts::QValueAxis;

SegmentQLineSeries::SegmentQLineSeries(QChart* _chart, QValueAxis* _xAxis, QValueAxis* _yAxis) :
	QObject(_chart),
	chart(_chart),
	xAxis(_xAxis),
	yAxis(_yAxis),
	numberOfPoints(0),
	width(1),
	lastSegmentType(INCREASING)
{
	segmentTypeColor.insert(INCREASING, Qt::red);
	segmentTypeColor.insert(DECREASING, Qt::black);

	segmentTypeIndexes.insert(INCREASING, QVector<int>());
	segmentTypeIndexes.insert(DECREASING, QVector<int>());
}

SegmentQLineSeries::~SegmentQLineSeries() {

}

void SegmentQLineSeries::append(QPointF point) {
	QLineSeries* lastSegment;
	QLineSeries* currentSegment;
	SegmentType currentSegmentType;
	
	if (numberOfPoints != 0) {
		lastSegment = segments.last();
		QPointF lastPointInSeries = lastSegment->at(lastSegment->count() - 1);
		currentSegmentType = point.y() <= lastPointInSeries.y() ? DECREASING : INCREASING;
	}
	
	if (currentSegmentType != lastSegmentType) {
		currentSegment = new QLineSeries(this);

		segments.append(currentSegment);

		lastSegmentType = lastSegmentType == INCREASING ? DECREASING : INCREASING;
		
		segmentTypeIndexes[lastSegmentType].append(segments.size() - 1);
		QPen pen;
		pen.setColor(segmentTypeColor[lastSegmentType]);
		pen.setWidth(width);
		currentSegment->setPen(pen);

		currentSegment->setUseOpenGL(true);
		chart->addSeries(currentSegment);
		
		currentSegment->attachAxis(xAxis);
		currentSegment->attachAxis(yAxis);
	}
	else {
		currentSegment = lastSegment;
	}

	currentSegment->append(point);
	numberOfPoints++;
}

void SegmentQLineSeries::clear() {
	numberOfPoints = 0;
	for (auto segment : segments) {
		chart->removeSeries(segment);
	}
	segments.clear();
	segmentTypeIndexes[INCREASING].clear();
	segmentTypeIndexes[DECREASING].clear();
}

void SegmentQLineSeries::setWidth(int _width) {
	width = _width;

	if (numberOfPoints == 0) {
		return;
	}

	QPen pen = segments[segmentTypeIndexes[INCREASING][0]]->pen();
	pen.setWidth(width);

	for (const auto& segmentIndex : segmentTypeIndexes[INCREASING]) {
		segments[segmentIndex]->setPen(pen);
	}

	pen = segments[segmentTypeIndexes[DECREASING][0]]->pen();
	pen.setWidth(width);

	for (const auto& segmentIndex : segmentTypeIndexes[DECREASING]) {
		segments[segmentIndex]->setPen(pen);
	}
}

void SegmentQLineSeries::setColor(QColor color, SegmentType segmentType) {

	QVector<int>& indexOfSegments = segmentTypeIndexes[segmentType];
	segmentTypeColor[segmentType] = color;
	
	if (indexOfSegments.size() == 0) {
		return;
	}

	QPen pen = segments[indexOfSegments[0]]->pen();
	pen.setColor(color);

	for (const auto& segmentIndex : indexOfSegments) {
		segments[segmentIndex]->setPen(pen);
	}
}

QPointF SegmentQLineSeries::getLastPoint() {
	return segments.last()->at(segments.last()->count() - 1);
}

int SegmentQLineSeries::size() {
	return numberOfPoints;
}