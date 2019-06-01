

class Medium
{
public:
	Medium(string id) :m_ID(id) {};
	string id() const { return m_ID; };
	virtual string connect()const = 0;
	virtual string transmit(string msg) const {
			return "text: " + msg;
	};
	virtual ~Medium() {};
private:
	string m_ID;
};

class TwitterAccount : public Medium
{
public:
	TwitterAccount(string id) :Medium(id) {};
	virtual string connect() const { return "Tweet"; };
	virtual ~TwitterAccount() { cout << "Destroying the Twitter account " << id() << "." << endl; };
};

class Phone : public Medium
{
public:
	Phone(string id, CallType type) : Medium(id), m_type(type) {};
	virtual string connect() const { return "Call"; };
	virtual ~Phone() { cout << "Destroying the phone " << id() << "." << endl; };
	virtual string transmit(string msg) const {
		if (m_type == VOICE)
		{
			return "voice: " + msg;
		}
		return "text: " + msg;
	};
private:
	CallType m_type;
};

class EmailAccount : public Medium
{
public:
	EmailAccount(string id) :Medium(id) {};
	virtual string connect() const { return "Email"; };
	virtual ~EmailAccount() { cout << "Destroying the email account " << id() << "." << endl; };
};




