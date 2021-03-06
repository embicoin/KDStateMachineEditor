/*
  semanticzoommanager.cpp

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

#include "semanticzoommanager.h"

#include "configurationcontroller.h"
#include "state.h"
#include "transition.h"
#include "elementwalker.h"
#include "widgets/statemachineview.h"
#include "statemachinescene.h"

using namespace KDSME;

SemanticZoomManager::SemanticZoomManager(QObject* parent)
    : QObject(parent)
    , m_configurationController(nullptr)
    , m_enabled(false)
{
}

ConfigurationController* SemanticZoomManager::configurationController() const
{
    return m_configurationController;
}

void SemanticZoomManager::setConfigurationController(ConfigurationController* controller)
{
    if (m_configurationController == controller)
        return;

    if (m_configurationController) {
        disconnect(m_configurationController, &ConfigurationController::activeConfigurationChanged,
                   this, &SemanticZoomManager::handleActiveConfigurationChanged);
    }
    m_configurationController = controller;
    if (m_configurationController) {
        connect(m_configurationController, &ConfigurationController::activeConfigurationChanged,
                this, &SemanticZoomManager::handleActiveConfigurationChanged);
    }
    emit configurationControllerChanged(m_configurationController);
}

bool SemanticZoomManager::isEnabled() const
{
    return m_enabled;
}

void SemanticZoomManager::setEnabled(bool enabled)
{
    if (m_enabled == enabled)
        return;

    m_enabled = enabled;
    emit enabledChanged(m_enabled);
}

void SemanticZoomManager::handleActiveConfigurationChanged(const QSet<State*>& configuration)
{
    if (!m_enabled)
        return;

    auto stateMachineView = m_configurationController->stateMachineView();
    auto view = stateMachineView->scene();
    auto root = stateMachineView->scene()->stateMachine();
    ElementWalker walker(ElementWalker::PreOrderTraversal);
    walker.walkChildren(root, [&](Element* i) -> ElementWalker::VisitResult {
        auto state = qobject_cast<State*>(i);
        if (!state) {
            return ElementWalker::RecursiveWalk;
        }

        const bool expand = configuration.contains(state);
        state->setExpanded(expand);
        return ElementWalker::RecursiveWalk;
    });

    view->layout();
}
