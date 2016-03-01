#ifndef UIHANDLE_H
#define UIHANDLE_H

#include <QObject>
#include <QWidget>
#include <QCheckBox>
#include <QFormLayout>
#include <QComboBox>
#include <QWidgetList>

///
/// \class UiHandle
///
/// This class is used as a connection between two UI-Classes, which do not have any other UI-connection.
/// As a first  start, it is used for a connection between kbwidget and rebindwidget.
/// In kbwidget is enough space for addition UI elements, in rebindwidget there is no space anyymore.
/// So ub kwbidget the object is created and as contructor parameter it gets a pointer to some
/// new, free UI element.
/// Later rebindwidget is creating another object and gets as static member the pointer
///  to the UI element from kbwidget.
///
/// \todo Yes, it is a hack and later we should reorganize the UI element hierarchy.

class UiHandle : public QObject
{
public:
    explicit UiHandle(QObject *parent = 0);
    ~UiHandle();

    static inline void setHandle(QObject* handleToAdditionalSpace) { staticHandle = handleToAdditionalSpace; }
    static inline QObject* getHandle() { return staticHandle; }

    /// \brief fill and release UI elements
    void setupUi (QStringList modkeys);
    void deleteUi ();

private:
    ///> Here we hold the pointer to the UI elemt, in which this class creates new ones
    static QObject *staticHandle;
    ///> All new elements hare held in this list
    static QWidgetList qWidgetList;
    void testfill(QComboBox* comboBox);

signals:

public slots:

};

#endif // UIHANDLE_H
