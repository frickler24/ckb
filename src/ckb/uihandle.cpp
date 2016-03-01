#include <QDebug>
#include "uihandle.h"

/// The static members
QObject* UiHandle::staticHandle = 0;
QWidgetList UiHandle::qWidgetList;

///
/// \brief UiHandle::UiHandle
/// \param parent
///
UiHandle::UiHandle(QObject *parent) :
    QObject(parent)
{
    if (parent) {
            setHandle(parent);
    }
}

UiHandle::~UiHandle() {
    deleteUi();
}

///
/// \brief UiHandle::setupUi
/// \param modkeys
///
/// Setup for additional apce in the UI.
/// First, for each modifier key a checkbox is created.
/// Last puts a ComboBox in the bottom row.
/// All UI elements are held together in qWidgetList.
///
void UiHandle::setupUi(QStringList modkeys) {

    int rows = modkeys.length();

    ///> Just create UI elements if not present and the handle is set (there exists a UI element to put new element into).
    if (getHandle() && qWidgetList.length() == 0) {
        QGridLayout *gridLayout = ((QGridLayout*)getHandle());  // Place all elements into a grid array

        ///> Create a lot of checkboxes for the modifier keys
        int i; // is used after loop again
        for (i = 0; i < rows; i++) {  // show two checkboxes per row
            QWidget* checkBox = new QCheckBox(modkeys[i]);
            qWidgetList.append(checkBox);
            qDebug() << modkeys[i] << checkBox;
            gridLayout->addWidget(checkBox, i/2, i%2);  // Alternatiig placement left, right; row by row
        }

        ///> Now create the ComboBox to display key/modifier-key combinations with active macro definitions
        QComboBox* comboBox = new QComboBox();
        qWidgetList.append(comboBox);
        comboBox->setMaximumWidth(175);
        testfill (comboBox);
        gridLayout->addWidget(comboBox, (i+1)/2, 0, 1, 2);
    }
}
void UiHandle::testfill(QComboBox* comboBox) {
    QStringList s;
    s.append("lshift+rshift+lalt+ralt+lwin+rwin+caps+fn+altgr+menu+lcontrol+lcontrol");
    s.append("lshift");
    s.append("rshift");
    s.append("lshift+rshift");
    s.append("lshift+lcontrol+lwin+lalt");
    comboBox->addItems(s);
}

///
/// \brief UiHandle::~UiHandle
/// Delete all UI elements and clear the element list
void UiHandle::deleteUi() {
    foreach (QWidget* qWidget, qWidgetList) {
        delete qWidget;
    }
    qWidgetList.clear();
}

