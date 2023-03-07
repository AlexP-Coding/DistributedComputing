class Reader
{
    private:
    char* filename;

    Reader(char* filename)
    {
        this->filename=filename;
    }

    ~Reader()
    {
        delete filename;
    }
};