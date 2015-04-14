#ifndef SYNCPAGE_H
#define SYNCPAGE_H

#include <QObject>
#include <QString>
#include <QVector>
#include "synctrack.h"

class SyncDocument;

class SyncPage : public QObject {
	Q_OBJECT
public:
	SyncPage(SyncDocument *document, const QString &name);

	SyncTrack *getTrack(int index);

	int getTrackCount() const
	{
		return trackOrder.size();
	}

	void addTrack(SyncTrack *);

	void swapTrackOrder(int t1, int t2)
	{
		Q_ASSERT(0 <= t1 && t1 < trackOrder.size());
		Q_ASSERT(0 <= t2 && t2 < trackOrder.size());
		std::swap(trackOrder[t1], trackOrder[t2]);
	}

public slots:
	// TODO: tighter invalidation on all of these!
	void onKeyFrameAdded(const SyncTrack &track, int)
	{
		invalidateTrack(track);
	}

	void onKeyFrameChanged(const SyncTrack &track, int, const SyncTrack::TrackKey &)
	{
		invalidateTrack(track);
	}

	void onKeyFrameRemoved(const SyncTrack &track, int)
	{
		invalidateTrack(track);
	}

	void invalidateTrack(const SyncTrack &track)
	{
		int trackIndex = trackOrder.indexOf((SyncTrack*)&track);
		Q_ASSERT(trackIndex >= 0);
		emit trackVisualChanged(trackIndex);
	}

private:
	SyncDocument *document;
	QString name;
	QVector<SyncTrack *> trackOrder;

signals:
	void trackVisualChanged(int trackIndex);
};

#endif // SYNCPAGE_H
