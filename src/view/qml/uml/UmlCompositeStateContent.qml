/*
  This file is part of the KDAB State Machine Editor Library.

  Copyright (C) 2014 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com.
  All rights reserved.
  Author: Kevin Funk <kevin.funk@kdab.com>

  Licensees holding valid commercial KDAB State Machine Editor Library
  licenses may use this file in accordance with the KDAB State Machine Editor
  Library License Agreement provided with the Software.

  This file may be distributed and/or modified under the terms of the
  GNU Lesser General Public License version 2.1 as published by the
  Free Software Foundation and appearing in the file LICENSE.LGPL.txt included.

  This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
  WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.

  Contact info@kdab.com if any conditions of this licensing are not
  clear to you.
*/

import QtQuick 2.0
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0

import com.kdab.kdsme 1.0 as KDSME

import "qrc:///kdsme/qml/util/"

Rectangle {
    id: root

    property bool roundedCorners: true

    // TODO: Tint background color based on level in hierarchy
    color: Theme.compositeStateBackgroundColor_Lightest
    border.color: Qt.tint(Theme.stateBorderColor, Theme.alphaTint(Theme.stateBorderColor_Active, activeness))
    border.width: (activeness > 0 ? 2 : 1)
    radius: roundedCorners ? 5 : 0

    Text {
        visible: !element.expanded

        anchors.centerIn: parent
        width: parent.width

        color: Theme.compositeStateLabelFontColor
        text: "..."
        horizontalAlignment: Text.AlignHCenter
    }
}
