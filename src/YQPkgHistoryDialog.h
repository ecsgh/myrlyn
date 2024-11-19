/*
  Copyright (c) 2000 - 2011 Novell, Inc.
  Copyright (c) 2018 - 2021 SUSE LLC

  This library is free software; you can redistribute it and/or modify
  it under the terms of the GNU Lesser General Public License as
  published by the Free Software Foundation; either version 2.1 of the
  License, or (at your option) version 3.0 of the License. This library
  is distributed in the hope that it will be useful, but WITHOUT ANY
  WARRANTY; without even the implied warranty of MERCHANTABILITY or
  FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public
  License for more details. You should have received a copy of the GNU
  Lesser General Public License along with this library; if not, write
  to the Free Software Foundation, Inc., 51 Franklin Street, Fifth
  Floor, Boston, MA 02110-1301 USA
*/

/*
  File:	      YQPkgHistoryDialog.h
  Author:     Stanislav Visnovsky <visnov@suse.com>
*/


#ifndef YQPkgHistoryDialog_h
#define YQPkgHistoryDialog_h

#include <QDialog>
#include <zypp/parser/HistoryLogReader.h>


class YQPkgList;
class YQPkgHistoryView;
class QTreeWidget;


/**
 * Pkg status and History as a standalone popup dialog.
 **/
class YQPkgHistoryDialog : public QDialog
{
    Q_OBJECT

public:

    /**
     * Static convenience method: Post a history dialog.
     **/
    static void showHistoryDialog( QWidget* parent = 0);


protected:

    /**
     * Constructor: Creates a dialog for the zypp history.
     * Use the static showHistoryDialog() method instead.
     **/
    YQPkgHistoryDialog( QWidget * parent );

    /**
     * Fill the trees with content.
     **/
    void populate();

    /**
     * Show a warning pop-up if there was an error reading the history file.
     **/
    void showReadHistoryWarning( const QString & message );


protected slots:

    void selectDate();
    void selectAction();


protected:

    // Data members

    QTreeWidget * _datesTree;   // Flat list for dates
    QTreeWidget * _actionsTree; // Tree with action items below date items
};


/**
 * Helper class to populate both tree widgets in this dialog with zypp history
 * actions.
 *
 * This is used as a functor for a zypp::parser::HistoryLogReader where it is
 * called for each history item found while parsing the history file.
 **/
class YQPkgHistoryItemCollector
{
public:

    /**
     * Constructor. This stores the widget pointers so items can later be added
     * to those trees when libzypp calls operator() for each history item.
     **/
    YQPkgHistoryItemCollector( QTreeWidget * datesTree,
                               QTreeWidget * actionsTree );

    /**
     * Functor method that is called by zypp::parser::HistoryLogReader for each
     * history item (for each action). This will add an item for the action
     * and, if needed, a parent item for the date and an item in the dates
     * tree.
     **/
    bool operator() ( const zypp::HistoryLogData::Ptr & item_ptr );

protected:

    /**
     * Add one item in the "dates" tree for the specified date.
     **/
    void addDatesTreeItem  ( const QString & actionDate );

    /**
     * Add one item in the "actions" tree for the specified date.
     * This item will act as the parent item for all actions on that date.
     **/
    void addActionsDateItem( const QString & actionDate );

    /**
     * Format columns for one action, depending on the action type.
     *
     * Return an empty QStringList if this is not an action that is suitable to
     * be shown to the user.
     **/
    QStringList actionColumns( const zypp::HistoryLogData::Ptr & item_ptr );

    /**
     * Return a suitable icon for an action.
     **/
    QPixmap actionIcon( zypp::HistoryActionID id );


    // Data members

    QTreeWidget *     _datesTree;
    QTreeWidget *     _actionsTree;
    QTreeWidgetItem * _actionsDateItem;  // parent item for all actions of this date
    QString           _lastDate;         // initialized empty like all QStrings
};


#endif // ifndef YQPkgHistoryDialog_h
