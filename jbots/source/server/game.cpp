#include <iostream>
#include <string>
#include <vector>

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

int main() {
	Match match;
	match.add( new TestBot( "test1" ) );
	match.add( new TestBot( "test2" ) );
	match.add( new Arena() );
	match.display();
}
