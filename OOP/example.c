typedef struct
{
    int (*get)(void* this);
    void (*set)(void* this, int i);
    int member;

} TheClass;

int Get(void* this)
{
    TheClass* This = (TheClass*)this;
    return This->member;
}

void Set(void* this, int i)
{
    TheClass* This = (TheClass*)this;
    This->member = i;
}

void init(TheClass* this)
{
    this->get = &Get;
    this->set = &Set;
}

int main(int argc, char **argv)
{
    TheClass name;
    init(&name);
    (name.set)(&name, 10);
    printf("%d\n", (name.get)(&name));
    return 0;
}
