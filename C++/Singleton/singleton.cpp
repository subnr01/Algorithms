classMySingleton {
public:

    staticMySingleton *GetInstance() 
    {
        if(m_pOnlyOneInstance==NULL) 
        {
            lock();
            if ( m_pOnlyOneInstance == NULL) 
            {
                m_pOnlyOneInstance = newMySingleton();
            }
            unlock();
        }
        return m_pOnlyOneInstance; 
    }
private: 
static MySingleton  *m_pOnlyOneInstance;
MySingleton();
};

