#ifndef TESTGITWIDGET_H
#define TESTGITWIDGET_H

#include <QFrame>
#include <QHash>
#include <QGridLayout>
#include <QLabel>

class TestGit;
class TestNetworkPlugin;
class TestGitWidget : public QFrame
{
    Q_OBJECT
public:
    TestGitWidget(TestGit *plugin, TestNetworkPlugin* testNetworkPlugin);

private:
    TestGit     *plugin;
    QGridLayout layout;

private slots:
    void test0();
    void test1();
    void test2();
    void test3();
	void created();
};

#endif // TESTGITWIDGET_H
