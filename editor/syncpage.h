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

	SyncTrack *getTrack(int index) const;

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
	void onKeyFrameChanged(const SyncTrack &track, int)
	{
		emit trackVisualChanged(track);
	}

private:
	SyncDocument *document;
	QString name;
	QVector<SyncTrack *> trackOrder;

signals:
	void trackVisualChanged(const SyncTrack &track);
};

#endif // SYNCPAGE_H
