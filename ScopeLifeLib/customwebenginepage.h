#ifndef CUSTOMWEBENGINEPAGE_H
#define CUSTOMWEBENGINEPAGE_H
#include <QWebEnginePage>
#include <QObject>

class CustomWebEnginePage : public QWebEnginePage
{

    Q_OBJECT

public:
    CustomWebEnginePage();

signals:

    void startCapture(QUrl url);
    void consoleMessage(JavaScriptConsoleMessageLevel level,const QString message);

public slots:
   void startWebCapture(QUrl url);
    void featureControl(const QUrl &origin, QWebEnginePage::Feature feature);


protected:
    bool certificateError(const QWebEngineCertificateError &certificateError) override ;
    bool acceptNavigationRequest(const QUrl &url, QWebEnginePage::NavigationType type, bool isMainFrame) override;
    QWebEnginePage * createWindow(WebWindowType type) override;
    bool  javaScriptConfirm(const QUrl &securityOrigin, const QString &msg) override;
    void javaScriptAlert(const QUrl &securityOrigin, const QString &msg) override;
    void javaScriptConsoleMessage(JavaScriptConsoleMessageLevel level, const QString &message, int lineNumber, const QString &sourceID);
};

#endif // CUSTOMWEBENGINEPAGE_H
