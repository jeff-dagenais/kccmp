#ifndef CONFIG_VIEW_HPP
#define CONFIG_VIEW_HPP
/*----------------------------------------------------------------------
 * $Id: config_view.hpp,v 1.4 2005-10-03 02:43:20 ganzhorn Exp $
 *
 * Copyright (C)   2005            Salem Ganzhorn <eyekode@yahoo.com>
 *
 * This file is part of kccmp - Kernel Config CoMPare
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of version 2 of the GNU General Public License
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *----------------------------------------------------------------------*/

#if KCCMP_QT_4
#include <QFrame>
#include <QObject>
#else
#include <qframe.h>
#include <qobject.h>
#endif

#include <set>
#include <string>

#include "config.hpp"

class QTabWidget;

class config_view : public QFrame {
    Q_OBJECT

public:
    explicit config_view( QWidget* parent = nullptr );

    void compare( const std::string& filename1,
        const std::string& filename2 );

protected:
    void add_diff_tab( QTabWidget* tab, const std::set<std::string>& info,
        const config& c1, const config& c2,
        const QString& dir1, const QString& dir2 );
    void add_set_tab( QTabWidget* tab,
        const std::set<std::string>& info,
        const config& c,
        const QString& label );
};

#endif
