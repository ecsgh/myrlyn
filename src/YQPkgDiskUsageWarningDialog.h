/*  ------------------------------------------------------
              __   _____  ____  _
              \ \ / / _ \|  _ \| | ____ _
               \ V / | | | |_) | |/ / _` |
                | || |_| |  __/|   < (_| |
                |_| \__\_\_|   |_|\_\__, |
                                    |___/
    ------------------------------------------------------

    Project:  YQPkg Package Selector
    Copyright (c) 2024 SUSE LLC
    License:  GPL V2 - See file LICENSE for details.

    Textdomain "qt-pkg"
 */


#ifndef YQPkgDiskUsageWarningDialog_h
#define YQPkgDiskUsageWarningDialog_h

#include <qdialog.h>


class YQPkgDiskUsageList;


/**
 * Warning dialog about partitions that are getting full or overflowing.
 **/
class YQPkgDiskUsageWarningDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * Static convenience method: Post a disk usage warning with text
     * 'message', a list of partitions that are at least 'thresholdPercent'
     * full and one ( default ) or two buttons.
     *
     * Returns 'true' if the user accepted ( i.e. clicked the 'accept' button )
     * and 'false' if the user rejected ( i.e. clicked the 'reject' button or
     * the window manager close button ).
     **/
    static bool diskUsageWarning( const QString & 	message,
				  int			thresholdPercent,
				  const QString &	acceptButtonLabel,
				  const QString &	rejectButtonLabel = QString() );
protected:

    /**
     * Constructor: Creates a disk usage warning dialog with text 'message' on
     * top, a list of partitions that are at least 'thresholdPercent' full and
     * one ( default ) or two buttons.
     *
     * Not meant for public use. Applications should use the static
     * 'diskUsageWarning' method instead.
     **/
    YQPkgDiskUsageWarningDialog( QWidget *		parent,
				 const QString & 	message,
				 int			thresholdPercent,
				 const QString &	acceptButtonLabel,
				 const QString &	rejectButtonLabel = QString() );
};


#endif // ifndef YQPkgDiskUsageWarningDialog_h
