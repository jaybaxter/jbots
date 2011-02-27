// Standard Library
#include <iostream>
#include <string>
#include <vector>

// Qt library
//#include <QApplication>
//#include <QtCore>
#include <QtGui>

class Bot {
public:
	typedef std::string Name;

	Bot( char const* const name ) : name_( name ) {}
	Bot( Bot const& other ) : name_( other.name() ) {}

	Name const& name() const { return name_; }
	void display() const { std::cout << "bot: " << name() << std::endl; }

	virtual void run() = 0;

private:
	Name name_;
};

class TestBot : public Bot {
public:
	TestBot( char const* const name ) : Bot( name ) {}
	virtual void run() { /* nothing */ }
};

class Arena {
public:
	void display() const {
		std::cout << "arena" << std::endl;
	}
};

class Match {
public:
	void add( Bot* const bot ) { bots_.push_back( bot ); }
	void add( Arena* const arena ) { arena_ = arena; }

	void display() const { 
		std::cout << "match" << std::endl;
		arena_->display();
		for ( Bots::const_iterator bot = bots_.begin();
			  bot != bots_.end();
			  ++bot )
		{
			(*bot)->display();
		}
	}

	~Match() {
		for ( Bots::iterator bot = bots_.begin();
			  bot != bots_.end();
			  ++bot )
		{
			delete *bot;
			*bot = NULL;
		}
		delete arena_;
	}
	
private:
	typedef std::vector<Bot*> Bots;
	Bots bots_;
	Arena* arena_;
};

class MainWindow : public QWidget {
public:
	MainWindow( QWidget* parent = 0 );
};

MainWindow::MainWindow( QWidget* parent )
	: QWidget( parent )
{
	setFixedSize(648, 400);
	
/*	QPushButton *quit = new QPushButton( tr( "Quit" ), this);
	quit->setGeometry( 62, 40, 75, 30 );
	quit->setFont( QFont( "Times", 18, QFont::Bold ) );
	
	connect( quit, SIGNAL( clicked() ), qApp, SLOT( quit() ) );
 */
}

int main( int argc, char** argv ) {
	QApplication app( argc, argv );
	MainWindow mainWindow;;
	mainWindow.show();

#if 0
	QTextEdit textEdit;
	textEdit.setReadOnly( true );
	textEdit.show();
#endif
	
	Match match;
	match.add( new TestBot( "test1" ) );
	match.add( new TestBot( "test2" ) );
	match.add( new Arena() );
	match.display();
	
	return app.exec();
}
