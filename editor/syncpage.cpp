#include "syncpage.h"

#include <syncdocument.h>

SyncPage::SyncPage(SyncDocument *document, const QString &name) :
    QObject(document),
    document(document),
    name(name)
{
}

SyncTrack *SyncPage::getTrack(int index) const
{
	Q_ASSERT(index >= 0 && index < trackOrder.size());
	return trackOrder[index];
}

void SyncPage::addTrack(SyncTrack *track)
{
	trackOrder.push_back(track);
	QObject::connect(track, SIGNAL(keyFrameAdded(const SyncTrack &, int)),
	                 this,  SLOT(onKeyFrameAdded(const SyncTrack &, int)));
	QObject::connect(track, SIGNAL(keyFrameChanged(const SyncTrack &, int, const TrackKey &)),
	                 this,  SLOT(onKeyFrameChanged(const SyncTrack &, int, const TrackKey &)));
	QObject::connect(track, SIGNAL(keyFrameRemoved(const SyncTrack &, int)),
	                 this,  SLOT(onKeyFrameRemoved(const SyncTrack &, int)));
}
