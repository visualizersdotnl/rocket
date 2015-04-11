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
	return document->getTrack(trackOrder[index]);
}
