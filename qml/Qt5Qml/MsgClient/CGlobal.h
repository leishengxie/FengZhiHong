/****************************************************************************


 ****************************************************************************/
#ifndef __CGLOBAL_H__
#define __CGLOBAL_H__


#define CC_PROPERTY_READONLY(varType, varName, funName)\
protected: varType varName;\
public: virtual varType get##funName(void) const;


/** CC_PROPERTY is used to declare a protected variable.
 We can use getter to read the variable, and use the setter to change the variable.
 @param varType     the type of variable.
 @param varName     variable name.
 @param funName     "get + funName" will be the name of the getter.
                    "set + funName" will be the name of the setter.
 @warning   The getter and setter are public virtual functions, you should rewrite them first.
            The variables and methods declared after CC_PROPERTY are all public.
            If you need protected or private, please declare.
 */
#define CC_PROPERTY(varType, varName, funName)\
protected: varType varName;\
public: virtual varType get##funName(void);\
public: virtual void set##funName(varType var);

/** CC_SYNTHESIZE_READONLY is used to declare a protected variable.
 We can use getter to read the variable.
 @param varType     the type of variable.
 @param varName     variable name.
 @param funName     "get + funName" will be the name of the getter.
 @warning   The getter is a public inline function.
            The variables and methods declared after CC_SYNTHESIZE_READONLY are all public.
            If you need protected or private, please declare.
 */
#define CC_SYNTHESIZE_READONLY(varType, varName, funName)\
protected: varType varName;\
public: virtual varType get##funName(void) const { return varName; }


/** CC_SYNTHESIZE is used to declare a protected variable.
 We can use getter to read the variable, and use the setter to change the variable.
 @param varType     the type of variable.
 @param varName     variable name.
 @param funName     "get + funName" will be the name of the getter.
                    "set + funName" will be the name of the setter.
 @warning   The getter and setter are public inline functions.
            The variables and methods declared after CC_SYNTHESIZE are all public.
            If you need protected or private, please declare.
 */
#define CC_SYNTHESIZE(varType, varName, funName)\
protected: varType varName;\
public: virtual varType get##funName(void) const { return varName; }\
public: virtual void set##funName(varType var){ varName = var; }


#define CC_SAFE_DELETE(p)           do { delete (p); (p) = nullptr; } while(0)
#define CC_SAFE_DELETE_ARRAY(p)     do { if(p) { delete[] (p); (p) = nullptr; } } while(0)
#define CC_SAFE_FREE(p)             do { if(p) { free(p); (p) = nullptr; } } while(0)
#define CC_BREAK_IF(cond)           if(cond) break

#endif //__CGLOBAL_H__
