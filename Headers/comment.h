#ifndef COMMENT_H
#define COMMENT_H

#include <string>

class Comment
{
private:
    std::string id, parentComment, paragraph, editor;

public:
    void buildComment();
    void printComment();
};

#endif