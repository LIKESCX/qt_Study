#include "qwmainwind.h"
#include "ui_qwmainwind.h"

QWMainWind::QWMainWind(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QWMainWind)
{
    ui->setupUi(this);
    iniUI();//iniUI()函数要在ui->setupUi(this)之后调用，两者的顺序不能调换。
    iniSignalSlots();
}

QWMainWind::~QWMainWind()
{
    delete ui;
}

//iniUI()函数 用于 创建那些代码写的界面组件，并添加到工具栏或状态栏
void QWMainWind::iniUI()
{
    //状态栏上添加组件
    fLabCurFile = new QLabel; //标签组件
    fLabCurFile->setMinimumWidth(150);
    fLabCurFile->setText(tr("当前文件："));
    ui->statusBar->addWidget(fLabCurFile);  //添加到状态栏
    progressBar1 = new QProgressBar;//进度条组件
    progressBar1->setMaximumWidth(200);
    progressBar1->setMinimum(5);
    progressBar1->setMaximum(50);
    progressBar1->setValue(ui->txtEdit->font().pointSize());
    ui->statusBar->addWidget(progressBar1); //添加到状态栏

    //工具栏添加组件
    spinFontSize = new QSpinBox;//文字大小 SpinBox
    spinFontSize->setMinimum(5);
    spinFontSize->setMaximum(50);
    spinFontSize->setValue(ui->txtEdit->font().pointSize());
    spinFontSize->setMinimumWidth(50);
    ui->mainToolBar->addWidget(new QLabel(tr("字体大小 ")));
    ui->mainToolBar->addWidget(spinFontSize);//将 SpinBox 添加到工具栏

    ui->mainToolBar->addSeparator();        //添加分隔条
    ui->mainToolBar->addWidget(new QLabel(tr(" 字体 ")));
    comboFont = new QFontComboBox;
    comboFont->setMinimumWidth(150);
    ui->mainToolBar->addWidget(comboFont);  //添加到工具栏

    setCentralWidget(ui->txtEdit);

}


void QWMainWind::on_actFontBold_triggered(bool checked)
{
    QTextCharFormat fmt;
    fmt = ui->txtEdit->currentCharFormat();
    if(checked)
        fmt.setFontWeight(QFont::Bold);
    else
        fmt.setFontWeight(QFont::Normal);
    ui->txtEdit->mergeCurrentCharFormat(fmt);
}

void QWMainWind::on_actFontItalic_triggered(bool checked)
{
    QTextCharFormat fmt;
    fmt = ui->txtEdit->currentCharFormat();
    fmt.setFontItalic(checked);
    ui->txtEdit->mergeCurrentCharFormat(fmt);
}

void QWMainWind::on_actFontUnder_triggered(bool checked)
{
    QTextCharFormat fmt;
    fmt = ui->txtEdit->currentCharFormat();
    fmt.setFontUnderline(checked);
    ui->txtEdit->mergeCurrentCharFormat(fmt);
}

void QWMainWind::on_txtEdit_copyAvailable(bool b)
{//更新 cut,copy,paste的enable属性
    ui->actCut->setEnabled(b);
    ui->actCopy->setEnabled(b);
    ui->actPaste->setEnabled(ui->txtEdit->canPaste());
}

void QWMainWind::on_txtEdit_selectionChanged()
{//更新粗体、斜体和下划线3种action的checked属性
    QTextCharFormat fmt;
    fmt = ui->txtEdit->currentCharFormat();     //获取文字的格式
    ui->actFontBold->setChecked(fmt.font().bold());   //是否粗体
    ui->actFontItalic->setChecked(fmt.fontItalic());   //是否斜体
    ui->actFontUnder->setChecked(fmt.fontUnderline());   //是否有下划线
}

void QWMainWind::iniSignalSlots()
{   //信号与槽的关联
    connect(spinFontSize,SIGNAL(valueChanged(int)),this,SLOT(on_spinBoxFontSize_valueChanged(int)));
    connect(comboFont,SIGNAL(currentIndexChanged(const QString &)),this,SLOT(on_comboFont_currentIndexChanged(const QString &)));
}

void QWMainWind::on_spinBoxFontSize_valueChanged(int aFontSize)
{   //改变字体大小的spinBox
    QTextCharFormat fmt;
    fmt = ui->txtEdit->currentCharFormat();
    fmt.setFontPointSize(aFontSize);    //设置字体大小
    ui->txtEdit->mergeCurrentCharFormat(fmt);
}

void QWMainWind::on_comboFont_currentIndexChanged(const QString &arg1)
{   //FontCombobox的响应，选择字体名称
    QTextCharFormat fmt;
    fmt = ui->txtEdit->currentCharFormat();
    fmt.setFontFamily(arg1);//设置字体名称
    ui->txtEdit->mergeCurrentCharFormat(fmt);
}

/*
    1.mergeCurrentCharFormat(fmt);合并字体属性,不调用fmt = ui->txtEdit->currentCharFormat();获取fmt也可以。
    2.setCurrentCharFormat(fmt);设置字体属性，会覆盖，字体其他属性，所以要配合fmt = ui->txtEdit->currentCharFormat();使用，才不会覆盖其他的字体属性。
*/






























