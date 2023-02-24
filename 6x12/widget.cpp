#include "widget.h"
#include "./ui_widget.h"
#include <QFileDialog>
#include <QAudioDevice>
#include <QMediaDevices>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    //Open file with database binds
    QDir::setCurrent("qrc:/content");
    file.setFileName("binds.txt");

    //Buttons that will be needed if there are more than 6 memes
    QPushButton *mass[12] = {ui->pushButton_1, ui->pushButton_2, ui->pushButton_3, ui->pushButton_4, ui->pushButton_5, ui->pushButton_6, ui->pushButton_7, ui->pushButton_8, ui->pushButton_9, ui->pushButton_10, ui->pushButton_11, ui->pushButton_12};
    for(int i = 6; i < 12; i++)
    {
        mass[i]->close();
    }

    //Only nambers can be entered in the textLine_1
    QValidator *validator = new QIntValidator(1, 6, this);
    ui->lineEdit_1->setValidator(validator);

    //URL sounds
    urlVol_arr = new QString[18];
    urlVol_arr_6 = new QString[6];

    //Keyboard buttons for bind
    str_key = new QString[18];

    //Player for sounds
    m_player = new QMediaPlayer(this);
    audio_Output = new QAudioOutput(this);
    m_player->setAudioOutput(audio_Output);

    //Reading file database
    file.open(QIODevice::ReadOnly);
    if(file.isOpen())
    {
        QString data;
        data = file.readAll();
        QStringList strs = data.split('\n');
        QStringList str;
        for(int i = 0; i < 18; i++)
        {
            str = strs[i].split(';');
            str_key[i] = str[0];
            urlVol_arr[i] = str[1];
        }
        for(int i = 0; i < 6; i++)
        {
            urlVol_arr_6[i] = urlVol_arr[i];
        }
    }
    else{
        file.close();
        file.open(QIODevice::WriteOnly);
        QTextStream writeStream(&file);
        for(int i = 0; i < 18; i++)
        {
            writeStream << "" << ';' << '\n';
        }
    }
    file.close();

    //Titles for comboBox
    titles6x12 << tr("6") << tr("12");
    ui->comboBox->addItems(titles6x12);
    ui->comboBox->setCurrentIndex(0);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::keyPressEvent(QKeyEvent *event)
{
    QString key = event->text();
    if(comboBox_index == 0) //ComboBox where 6 buttons
    {
        for(int i = 0; i < 6; i++)
        {
            if(key == str_key[i])
            {
                m_player->stop();
                m_player->setSource(urlVol_arr_6[i]);
                m_player->play();
            }
        }
    }
    else{ //ComboBox where 12 buttons
        for(int i = 6; i < 18; i++)
        {
            if(key == str_key[i])
            {
                m_player->stop();
                m_player->setSource(urlVol_arr[i]);
                m_player->play();
            }
        }
    }
}

void Widget::on_lineEdit_1_editingFinished() //lineEdit button number
{
    LineEdit_1_num = ui->lineEdit_1->text().toInt();
}

void Widget::on_lineEdit_2_editingFinished() //lineEdit keyboard button
{
    LineEdit_2 = ui->lineEdit_2->text().toUpper();
}

void Widget::on_pushButton_clicked() //Click Button that bind url and key
{
    QFileDialog dialog = QFileDialog(this);
    QString str_url = dialog.getOpenFileName(this, tr("Choose audio file"), "", "MP3 files(*.mp3*)"); //Using only mp3 to audio files
    if(str_url == ""){} //if no audio url do nothing
    else{
        file.open(QIODevice::WriteOnly);
        if(file.isOpen())
        { //Write urls and keys in database binds.txt
            QTextStream writeStream(&file);
            if(comboBox_index == 0)
            { //ComboBox 6 buttons
                urlVol_arr_6[LineEdit_1_num-1] = urlVol_arr[LineEdit_1_num-1] = str_url;
                str_key[LineEdit_1_num-1] = LineEdit_2;
            }
            else{ //ComboBox 12 buttons
                urlVol_arr[LineEdit_1_num+5] = str_url;
            }
            for(int i = 0; i < 18; i++)
            {
                writeStream << str_key[i] << ';' << urlVol_arr[i] << '\n';
            }
            for(int i = 0, j = 6; i < 6; i++, j++)
            {
                urlVol_arr_6[i] = urlVol_arr[j];
            }
            file.flush();
            file.close();
            ui->comboBox->activated(comboBox_index);
        }
    }
}

void Widget::on_pushButton_13_clicked() //Clear all binds
{
    file.open(QIODevice::WriteOnly);
    QTextStream writeStream(&file);
    for(int i = 0; i < 18; i++)
    {
        if(i < 6)
        {
            urlVol_arr[i] = "";
            urlVol_arr_6[i] = "";
            str_key[i] = "";
        }
        else{
            urlVol_arr[i] = "";
            str_key[i] = "";
        }
        writeStream << "" << ';' << '\n';
    }
}

void Widget::on_pushButton_1_clicked()
{
    m_player->stop();
    m_player->setSource(urlVol_arr_6[0]);
    if(urlVol_arr_6[0] == "")
    {
        lbl = new QLabel;
        lbl->setText("No audio link for this button");
        lbl->show();
    }
    else{
        m_player->play();
    }
}

void Widget::on_pushButton_2_clicked()
{
    m_player->stop();
    m_player->setSource(urlVol_arr_6[1]);
    if(urlVol_arr_6[1] == "")
    {
        lbl = new QLabel;
        lbl->setText("No audio link for this button");
        lbl->show();
    }
    else{
        m_player->play();
    }
}

void Widget::on_pushButton_3_clicked()
{
    m_player->stop();
    m_player->setSource(urlVol_arr_6[2]);
    if(urlVol_arr_6[2] == "")
    {
        lbl = new QLabel;
        lbl->setText("No audio link for this button");
        lbl->show();
    }
    else{
        m_player->play();
    }
}

void Widget::on_pushButton_4_clicked()
{
    m_player->stop();
    m_player->setSource(urlVol_arr_6[3]);
    if(urlVol_arr_6[3] == "")
    {
        lbl = new QLabel;
        lbl->setText("No audio link for this button");
        lbl->show();
    }
    else{
        m_player->play();
    }
}

void Widget::on_pushButton_5_clicked()
{
    m_player->stop();
    m_player->setSource(urlVol_arr_6[4]);
    if(urlVol_arr_6[4] == "")
    {
        lbl = new QLabel;
        lbl->setText("No audio link for this button");
        lbl->show();
    }
    else{
        m_player->play();
    }
}

void Widget::on_pushButton_6_clicked()
{
    m_player->stop();
    m_player->setSource(urlVol_arr_6[5]);
    if(urlVol_arr_6[5] == "")
    {
        lbl = new QLabel;
        lbl->setText("No audio link for this button");
        lbl->show();
    }
    else{
        m_player->play();
    }
}

void Widget::on_pushButton_7_clicked()
{
    m_player->stop();
    m_player->setSource(urlVol_arr[12]);
    if(urlVol_arr[12] == "")
    {
        lbl = new QLabel;
        lbl->setText("No audio link for this button");
        lbl->show();
    }
    else{
        m_player->play();
    }
}

void Widget::on_pushButton_8_clicked()
{
    m_player->stop();
    m_player->setSource(urlVol_arr[13]);
    if(urlVol_arr[13] == "")
    {
        lbl = new QLabel;
        lbl->setText("No audio link for this button");
        lbl->show();
    }
    else{
        m_player->play();
    }
}

void Widget::on_pushButton_9_clicked()
{
    m_player->stop();
    m_player->setSource(urlVol_arr[14]);
    if(urlVol_arr[14] == "")
    {
        lbl = new QLabel;
        lbl->setText("No audio link for this button");
        lbl->show();
    }
    else{
        m_player->play();
    }
}

void Widget::on_pushButton_10_clicked()
{
    m_player->stop();
    m_player->setSource(urlVol_arr[15]);
    if(urlVol_arr[15] == "")
    {
        lbl = new QLabel;
        lbl->setText("No audio link for this button");
        lbl->show();
    }
    else{
        m_player->play();
    }
}

void Widget::on_pushButton_11_clicked()
{
    m_player->stop();
    m_player->setSource(urlVol_arr[16]);
    if(urlVol_arr[16] == "")
    {
        lbl = new QLabel;
        lbl->setText("No audio link for this button");
        lbl->show();
    }
    else{
        m_player->play();
    }
}

void Widget::on_pushButton_12_clicked()
{
    m_player->stop();
    m_player->setSource(urlVol_arr[17]);
    if(urlVol_arr[17] == "")
    {
        lbl = new QLabel;
        lbl->setText("No audio link for this button");
        lbl->show();
    }
    else{
        m_player->play();
    }
}

void Widget::on_comboBox_activated(int index) //ComboBox with titles 6 and 12
{
    if(index == 0)
    {
        comboBox_index = index;
        //Only nambers 1-6 can be entered in the textLine_1
        QValidator *validator = new QIntValidator(1, 6, this);
        ui->lineEdit_1->setValidator(validator);

        // Initialization Array of 6 first buttons
        for(int i = 0; i < 6; i++)
        {
            urlVol_arr_6[i] = urlVol_arr[i];
        }

        QPushButton *mass[12] = {ui->pushButton_1, ui->pushButton_2, ui->pushButton_3, ui->pushButton_4, ui->pushButton_5, ui->pushButton_6, ui->pushButton_7, ui->pushButton_8, ui->pushButton_9, ui->pushButton_10, ui->pushButton_11, ui->pushButton_12};
        for(int i = 6; i < 12; i++)
        {
            mass[i]->close();
        }
        //Make less scroll area for 6 buttons
        ui->scrollAreaWidgetContents_6->setMinimumHeight(499);
        ui->frame->setMinimumHeight(499);
    }
    else if(index == 1)
    {
        comboBox_index = index;
        //Only nambers 1-12 can be entered in the textLine_1
        QValidator *validator = new QIntValidator(1, 12, this);
        ui->lineEdit_1->setValidator(validator);

        // Initialization Array of 6 first buttons
        for(int i = 0, j = 6; i < 6; i++, j++)
        {
            urlVol_arr_6[i] = urlVol_arr[j];
        }

        QPushButton *mass[12] = {ui->pushButton_1, ui->pushButton_2, ui->pushButton_3, ui->pushButton_4, ui->pushButton_5, ui->pushButton_6, ui->pushButton_7, ui->pushButton_8, ui->pushButton_9, ui->pushButton_10, ui->pushButton_11, ui->pushButton_12};

        //Make more scroll area for 12 buttons
        ui->scrollAreaWidgetContents_6->setMinimumHeight(900);
        ui->frame->setMinimumHeight(900);

        //Set Geometry for 6 down buttons
        ui->pushButton_7->setGeometry(130, 500, 150, 150);
        ui->pushButton_8->setGeometry(320, 500, 150, 150);
        ui->pushButton_9->setGeometry(510, 500, 150, 150);
        ui->pushButton_10->setGeometry(130, 710, 150, 150);
        ui->pushButton_11->setGeometry(320, 710, 150, 150);
        ui->pushButton_12->setGeometry(510, 710, 150, 150);

        for(int i = 6; i < 12; i++)
        {
            mass[i]->show();
        }
    }
}
