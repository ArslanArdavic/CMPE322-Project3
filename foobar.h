struct foobar {
    foo mutex;
};

void InitFoobar(foobar* foo)
{
   oneCreate(&foo->mutex);
}

void FreeFoobar(foobar* foo)
{
   oneDestroy(foo->mutex);
}

struct foobar fooStruct;
InitFoobar(&fooStruct);
// ..
FreeFoobar(&fooStruct);