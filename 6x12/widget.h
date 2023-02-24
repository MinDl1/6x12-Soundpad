#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QFile>
#include <QKeyEvent>
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_1_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_7_clicked();
    void on_pushButton_8_clicked();
    void on_pushButton_9_clicked();
    void on_pushButton_10_clicked();
    void on_pushButton_11_clicked();
    void on_pushButton_12_clicked();
    void on_pushButton_13_clicked();

    void on_comboBox_activated(int index);
    void on_lineEdit_1_editingFinished();
    void on_lineEdit_2_editingFinished();

private:
    void keyPressEvent(QKeyEvent *event);

private:
    Ui::Widget *ui;
    QMediaPlayer *m_player; //Player for sounds
    QAudioOutput *audio_Output; //AudioOutput for player
    QStringList titles6x12; //Titles list for ComboBox
    QString *urlVol_arr; //Array of all 18 audio urls
    QString *urlVol_arr_6; //Array of audio urls for 6 firs buttons
    QString *str_key; //Array of bind keyboard buttons
    QString *file_name; //txt file name(database of urls and keyboard buttons)
    int LineEdit_1_num; //Number of button that user want bind
    QString LineEdit_2; //Keyboard button that user want bind
    QFile file; //txt file(database)
    int comboBox_index; //ComboBox current index
    QLabel *lbl;
};
#endif // WIDGET_H
