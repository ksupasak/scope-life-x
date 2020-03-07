#include "webcontroller.h"
#include "ui_webcontroller.h"
#include <QWebEngineProfile>
#include "customwebenginepage.h"
#include <QColor>
WebController::WebController(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WebController)
{
    ui->setupUi(this);

    view = new QWebEngineView(this);

    // add to main video view
    QLayout *layout = new QHBoxLayout();
    layout->setMargin(0);
    layout->addWidget(view);
    ui->view->setLayout(layout);

//    view->setUrl( QUrl(QStringLiteral("https://apple.com")));

//    view->page()->profile()->setPersistentCookiesPolicy(QWebEngineProfile::ForcePersistentCookies);


    connect(view,&QWebEngineView::urlChanged, this,&WebController::urlChanged);
    connect(view,&QWebEngineView::loadStarted, this,&WebController::loadStarted);
    connect(view,&QWebEngineView::loadFinished, this,&WebController::loadFinished);
    connect(view,&QWebEngineView::loadProgress, this,&WebController::loadProgress);



}

WebController::~WebController()
{
    delete ui;
}

void WebController::setUrl(const QUrl &url)
{

    if(current_page!=NULL){

        current_page->action(QWebEnginePage::Stop);
        delete current_page;
        current_page = NULL;
    }

    ui->url->setText(url.toString());
    CustomWebEnginePage *page = new CustomWebEnginePage();
    page->profile()->setPersistentCookiesPolicy(QWebEngineProfile::ForcePersistentCookies);
    page->setUrl(url);
    view->setPage(page);
    page->setBackgroundColor(QColor(0,0,0));
    connect(page, &CustomWebEnginePage::startCapture, this,&WebController::startCaptureRequest);
    connect(page, &CustomWebEnginePage::consoleMessage, this,&WebController::consoleMessage);




    current_page = page;

}

void WebController::on_go_btn_clicked()
{
    view->setUrl( QUrl(ui->url->text()));

}

void WebController::urlChanged(const QUrl &url)
{
    ui->url->setText(url.toString());

}

void WebController::loadStarted()
{
    ui->progress->setValue(0);
}

void WebController::startCaptureRequest(const QUrl &url)
{
    emit startCapture(url);
}

void WebController::loadFinished(bool ok)
{
    ui->progress->setValue(100);
}

void WebController::loadProgress(int progress)
{
    ui->progress->setValue(progress);
}

void WebController::on_next_btn_clicked()
{
    view->forward();

}

void WebController::on_back_btn_clicked()
{
    view->back();
}

void WebController::on_exit_btn_clicked()
{
    emit back();
}

void WebController::setCore(CoreLib *core)
{
    this->core = core;
}

void WebController::finish()
{
   if(core->hasCurrentSession()){
    QString ssid = core->getCurrentSession()->getSsid();
    view->page()->runJavaScript("addAttachment('"+ssid+"')", [](const QVariant &v) { qDebug() << v.toString(); });
   }

}

void WebController::on_url_returnPressed()
{
    view->setUrl( QUrl(ui->url->text()));
}

void WebController::consoleMessagePage(QWebEnginePage::JavaScriptConsoleMessageLevel level, const QString &message)
{
    emit consoleMessage(level,message);
}
