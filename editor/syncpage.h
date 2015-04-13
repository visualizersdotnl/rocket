#ifndef SYNCPAGE_H
#define SYNCPAGE_H

#include <QObject>
#include <QString>
#include <QVector>

class SyncDocument;
class SyncTrack;

class SyncPage : public QObject {
	Q_OBJECT
public:
	SyncPage(SyncDocument *document, const QString &name);

	int getTrackIndex(int index) const
	{
		return trackOrder[index];
	}

	SyncTrack *getTrack(int index) const;

	int getTrackCount() const
	{
		return trackOrder.size();
	}

	int addTrack(int trackIndex)
	{
		trackOrder.push_back(trackIndex);
		return trackOrder.size() - 1;
	}

	void swapTrackOrder(int t1, int t2)
	{
		Q_ASSERT(0 <= t1 && t1 < trackOrder.size());
		Q_ASSERT(0 <= t2 && t2 < trackOrder.size());
		std::swap(trackOrder[t1], trackOrder[t2]);
	}

private:
	SyncDocument *document;
	QString name;
	QVector<int> trackOrder;
};

#endif // SYNCPAGE_H
