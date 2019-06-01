#ifndef PLA_H
#define PLA_H

#include "Side.h"
#include "Board.h"
#include <string>

#include <chrono>
#include <future>
#include <atomic>

class AlarmClock
{
public:
	AlarmClock(int ms)
	{
		m_timedOut = false;
		m_isRunning = true;
		m_alarmClockFuture = std::async([=]() {
			for (int k = 0; k < ms && m_isRunning; k++)
				std::this_thread::sleep_for(std::chrono::milliseconds(1));
			if (m_isRunning)
				m_timedOut = true;
		});
	}

	~AlarmClock()
	{
		m_isRunning = false;
		m_alarmClockFuture.get();
	}

	bool timedOut() const
	{
		return m_timedOut;
	}

	AlarmClock(const AlarmClock&) = delete;
	AlarmClock& operator=(const AlarmClock&) = delete;
private:
	std::atomic<bool> m_isRunning;
	std::atomic<bool> m_timedOut;
	std::future<void> m_alarmClockFuture;
};

class Player 
{
public:
	Player(std::string name) :m_name(name) {};
	std::string name() const;
	virtual bool isInteractive() const;
	virtual int chooseMove(const Board& b, Side s) const = 0;
	virtual ~Player() {};

private:
	std::string m_name;
};

class HumanPlayer : public Player
{
public:
	HumanPlayer(std::string name) :Player(name){};
	virtual bool isInteractive() const { return true; };
	virtual int chooseMove(const Board& b, Side s) const;
	virtual ~HumanPlayer() {};
};

class BadPlayer : public Player
{
public:
	BadPlayer(std::string name) : Player(name) {};
	virtual int chooseMove(const Board& b, Side s) const;
	virtual ~BadPlayer() {};
};

class SmartPlayer : public Player
{
public:
	SmartPlayer(std::string name) : Player(name),m_depth(5){};
	virtual int chooseMove(const Board& b, Side s) const;
	virtual ~SmartPlayer() {};
private:
	int evaluate(const Board& b, const Side& s, const int& depth) const;
	void choose(Side s, const Board& b, int& bestHole, int& difference, const int& depth, AlarmClock& ac) const; // a recursive function to determine the move 
	int whichSide(const int& depth) const; // return 1 if this is smartplayer's turn, -1 if this is the opponent's turn
	int m_depth;
};



#endif // !PLA_H

