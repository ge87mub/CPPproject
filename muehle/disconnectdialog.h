#ifndef DISCONNECTDIALOG_H
#define DISCONNECTDIALOG_H

#include <QDialog>

namespace Ui {
class DisconnectDialog;
}
/**
 * @class DisconnectDialog
 * @brief Used to confirm exit mid game
 */
class DisconnectDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Constructor for DisconnectDialog.
     * @param parent Parent widget pointer.
     */
    explicit DisconnectDialog(QWidget *parent = nullptr);

    /**
     * @brief Destructor for DisconnectDialog.
     */
    ~DisconnectDialog();

private:

    /**
     * @brief Pointer to the UI generated by Qt Designer.
     */
    Ui::DisconnectDialog *ui;
};

#endif // DISCONNECTDIALOG_H
