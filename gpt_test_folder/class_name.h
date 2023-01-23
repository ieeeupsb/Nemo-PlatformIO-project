#pragma once

class note {
  private:
    string to;
    string from;
    string heading;
    string body;
  public:
    note(string to, string from, string heading, string body);
    string getTo();
    string getFrom();
    string getHeading();
    string getBody();
};

note::note(string to, string from, string heading, string body) {
  this->to = to;
  this->from = from;
  this->heading = heading;
  this->body = body;
}

string note::getTo() {
  return to;
}

string note::getFrom() {
  return from;
}

string note::getHeading() {
  return heading;
}

string note::getBody() {
  return body;
}