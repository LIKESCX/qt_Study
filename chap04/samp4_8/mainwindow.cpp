#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    LabFileName = new QLabel("");
    ui->statusBar->addWidget(LabFileName);
    /*
     * 将ScrollArea组件设置为主窗口工作区的中心组件后，
     * DockWidget与ScrollArea之间自动出现分割条，可以分割两个组件的大小
     */
    this->setCentralWidget(ui->scrollArea);
    initTree();//初始化目录树
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::initTree()
{//初始化目录树
    QString dataStr = "";   //Item 的Data 存储的string
    ui->treeFiles->clear();
    QIcon icon;
    icon.addFile(":/images/icons/15.ico");

    QTreeWidgetItem* item = new QTreeWidgetItem(MainWindow::itTopItem);
    item->setIcon(MainWindow::colItem,icon);  //第1列的图标
    item->setText(MainWindow::colItem,"图片文件"); //第1列的文字
    item->setText(MainWindow::colItemType,"type=itTopItem"); //第2列
    item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsAutoTristate);
    item->setCheckState(colItem,Qt::Checked);

    item->setData(MainWindow::colItem, Qt::UserRole, QVariant(dataStr));
    ui->treeFiles->addTopLevelItem(item);//添加顶层节点
}


//执行actAddFolder的槽函数
void MainWindow::on_actAddFolder_triggered()
{//添加组节点
    qDebug()<<"添加组节点";
    QString dir = QFileDialog::getExistingDirectory();//选择目录
    if(!dir.isEmpty())
    {
        QTreeWidgetItem *parItem = ui->treeFiles->currentItem(); //当前节点
        if(parItem == Q_NULLPTR){
           qDebug()<< "没有选择父节点";
           return;//防止程序崩溃
        }
        addFolderItem(parItem, dir);//父节点下面添加一个组节点
    }
    qDebug()<<"请先选择顶层节点";
    return;
}

void MainWindow::addFolderItem(QTreeWidgetItem *parItem, QString dirName)
{//添加一个组节点
    qDebug()<<"添加一个组节点";
    QIcon icon(":/images/icons/open3.bmp");
    QString nodeText = getFinalFolderName(dirName);//获得最后的文件夹名称
    QTreeWidgetItem *item = Q_NULLPTR;
    item = new QTreeWidgetItem(MainWindow::itGroupItem);//节点类型itGroupItem
    item->setIcon(colItem,icon);//或者写完整的MainWindow::colItem,这里可以省略MainWindow::
    item->setText(colItem,nodeText);
    item->setText(colItemType,"type=itGroupItem");
    item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsAutoTristate);
    item->setCheckState(colItem,Qt::Checked);
    item->setData(colItem,Qt::UserRole,QVariant(dirName));
    parItem->addChild(item);//在父节点下面添加子节点
}

QString MainWindow::getFinalFolderName(const QString &fullPathName)
{//从一个完整目录名称里，获得最后的文件夹名称
    qDebug()<<"从一个完整目录名称里，获得最后的文件夹名称";
    int cnt = fullPathName.length();
    int i = fullPathName.lastIndexOf("/");
    QString str = fullPathName.right(cnt-i-1);
    return str;
}


void MainWindow::on_actAddFiles_triggered()
{//添加图片文件节点
    QStringList files = QFileDialog::getOpenFileNames(this,"选择一个或多个文件","","Images(*.jpg)");//手动修改文件名后缀的图片文件，也打不开，必须原始文件就是这里的格式
    if(files.isEmpty())
        return;
    QTreeWidgetItem *parItem = Q_NULLPTR,*item = Q_NULLPTR;
    item = ui->treeFiles->currentItem();
    if(item->type()==itImageItem)//当前节点是图片节点
        parItem = item->parent();
    else
        parItem = item;

    for (int i = 0; i < files.size() ; ++i )
    {
        QString aFileName = files.at(i);//得到一个文件名
        addImageItem(parItem,aFileName);//添加一个图片节点
    }

}

void MainWindow::addImageItem(QTreeWidgetItem *parItem, QString aFileName)
{//添加一个图片文件节点
    QIcon icon(":/images/icons/31.ico");
    QString nodeText = getFinalFolderName(aFileName);//获得最后的文件名称
    QTreeWidgetItem *item = Q_NULLPTR;
    item = new QTreeWidgetItem(itImageItem);//节点类型为itImageItem
    item->setText(colItem,nodeText);
    item->setText(colItemType,"type=itImageItem");
    item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsAutoTristate);
    item->setCheckState(colItem,Qt::Checked);
    item->setData(colItem,Qt::UserRole,QVariant(aFileName));
    parItem->addChild(item);//在父节点下面添加子节点

}


void MainWindow::on_treeFiles_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{//当前节点变化时的处理
    Q_UNUSED(previous);
    if (current == Q_NULLPTR)
        return;
    int var = current->type();//节点类型
    switch (var) {
        case itTopItem: //顶层节点
            ui->actAddFolder->setEnabled(true);
            ui->actAddFiles->setEnabled(true);
            ui->actDeleteItem->setEnabled(true);
            break;
        case itGroupItem: //组节点
            ui->actAddFolder->setEnabled(true);
            ui->actAddFiles->setEnabled(true);
            ui->actDeleteItem->setEnabled(true);
            break;
        case itImageItem: //图片文件节点
            ui->actAddFolder->setEnabled(false);//图片节点不能添加目录节点
            ui->actAddFiles->setEnabled(true);
            ui->actDeleteItem->setEnabled(true);
            displayImage(current);
            break;
    }

}


void MainWindow::on_actDeleteItem_triggered()
{//删除节点
    QTreeWidgetItem *item = ui->treeFiles->currentItem();//当前节点
//    int childCount = item->childCount();
//    qDebug() << "子节点数量: " << childCount;

//    QTreeWidgetItem *parItem = item->parent();//父节点
//    //Removes the given item indicated by child. The removed item will not be deleted.需手动delete
//    parItem->removeChild(item);//移除一个子节点，并不会删除
//    delete  item;
    //以上书上提供的方法只能删除当前节点，当前节点下的子节点，及子子节点 都没有被删除，程序有问题。
    removeItem(item);//采用这种方法 可以删除干净
}

//递归删除节点 --书上没有 自己完善的
void MainWindow::removeItem(QTreeWidgetItem *item)
{
    int count = item->childCount();
    if(count == 0)//没有子节点，直接删除
    {
        QString localText = item->text(colItem);
        qDebug() << "删除子节点 " << localText;
        delete item;
        return;
    }
    for(int i=0; i<count; i++)
    {
        QTreeWidgetItem *childItem = item->child(0);//删除子节点
        removeItem(childItem);
    }
    QString localText = item->text(colItem);
    qDebug() << "最后将自己删除 " << localText;
    delete item;//最后将自己删除
}

void MainWindow::on_actScanItems_triggered()
{//遍历节点
    for (int i = 0; i < ui->treeFiles->topLevelItemCount();i++ ) {
        QTreeWidgetItem *item = ui->treeFiles->topLevelItem(i);//顶层节点
        changeItemCaption(item);//更改节点标题
    }
}

void MainWindow::changeItemCaption(QTreeWidgetItem *item)
{//改变节点的标题文字
    QString str = "*" + item->text(colItem);  //节点标题前
    item->setText(colItem,str);
    if(item->childCount()>0)
        for (int i = 0; i < item->childCount(); i++ )//遍历子节点
            changeItemCaption(item->child(i));//调用自己，可重入的函数

}

void MainWindow::displayImage(QTreeWidgetItem *item)
{//显示图片，节点item存储了图片文件名
    qDebug() << "显示图片，节点item存储了图片文件名";
    QString filename = item->data(colItem,Qt::UserRole).toString();//文件名
    LabFileName->setText(filename);
    qDebug() << filename;
    //A null pixmap has zero width, zero height and no contents. You cannot draw in a null pixmap. 是刚执行QPixmap curPixmap;创建的时候默认初始化
    if(curPixmap.isNull()){
        qDebug() << "is null....1";
    }
    bool localLoad = curPixmap.load(filename);
    qDebug() << "localLoad" << localLoad;//当能真正找到并格式包括解析没问题的话，返回true。
    if(curPixmap.isNull()){
        qDebug() << "is null....2";//当根据文件名找不到具体文件，或者文件名的后缀被手动改过。
    }
    on_actZoomFitH_triggered();//自动适应高度显示
}



void MainWindow::on_actZoomFitH_triggered()
{//适应高度显示图片
    qDebug() << "适应高度显示图片";
    int H = ui->scrollArea->height();
    qDebug() << "H =" << H;
    int realH = curPixmap.height();
    qDebug() << "realH =" << realH;
    pixRatio = float(H)/realH; //当前显示比例，必须转换为浮点数
    QPixmap pix = curPixmap.scaledToHeight(H-30);//图片缩放到指定高度
    //这里注意UI上LabPicture是否在scrollArea里面，如果层级不对，是展示不出图片的。会闪退
    ui->LabPicture->setPixmap(pix);
}


void MainWindow::on_actZoomIn_triggered()
{//放大显示
    pixRatio=pixRatio*1.2;
    int w = pixRatio*curPixmap.width();
    int h = pixRatio*curPixmap.height();
    QPixmap pix = curPixmap.scaled(w,h);
    ui->LabPicture->setPixmap(pix);
}


void MainWindow::on_actZoomRealSize_triggered()
{//实际大小显示
    pixRatio=1;
    ui->LabPicture->setPixmap(curPixmap);
}


void MainWindow::on_actDockVisible_triggered(bool arg1)
{//停靠区的可见性
    ui->dockWidget->setVisible(arg1);
}


void MainWindow::on_actDockFloat_triggered(bool checked)
{//停靠区浮动性
    qDebug() << "停靠区浮动性" << checked;
    ui->dockWidget->setFloating(checked);
}


void MainWindow::on_dockWidget_visibilityChanged(bool visible)
{//停靠区可见性变化
    ui->actDockVisible->setChecked(visible);
}


void MainWindow::on_dockWidget_topLevelChanged(bool topLevel)
{//停靠区浮动性变化
    ui->actDockFloat->setChecked(topLevel);
}
