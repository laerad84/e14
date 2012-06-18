//
// File generated by rootcint at Sun Jun  3 02:38:16 2012

// Do NOT change. Changes will be lost next time file is generated
//

#define R__DICTIONARY_FILENAME srcdIGsimRunDataDict
#include "RConfig.h" //rootcint 4834
#if !defined(R__ACCESS_IN_SYMBOL)
//Break the privacy of classes -- Disabled for the moment
#define private public
#define protected public
#endif

// Since CINT ignores the std namespace, we need to do so in this file.
namespace std {} using namespace std;
#include "GsimRunDataDict.h"

#include "TClass.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"

// START OF SHADOWS

namespace ROOT {
   namespace Shadow {
   } // of namespace Shadow
} // of namespace ROOT
// END OF SHADOWS

namespace ROOT {
   void GsimRunData_ShowMembers(void *obj, TMemberInspector &R__insp);
   static void *new_GsimRunData(void *p = 0);
   static void *newArray_GsimRunData(Long_t size, void *p);
   static void delete_GsimRunData(void *p);
   static void deleteArray_GsimRunData(void *p);
   static void destruct_GsimRunData(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::GsimRunData*)
   {
      ::GsimRunData *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::GsimRunData >(0);
      static ::ROOT::TGenericClassInfo 
         instance("GsimRunData", ::GsimRunData::Class_Version(), "././GsimData/GsimRunData.h", 22,
                  typeid(::GsimRunData), DefineBehavior(ptr, ptr),
                  &::GsimRunData::Dictionary, isa_proxy, 4,
                  sizeof(::GsimRunData) );
      instance.SetNew(&new_GsimRunData);
      instance.SetNewArray(&newArray_GsimRunData);
      instance.SetDelete(&delete_GsimRunData);
      instance.SetDeleteArray(&deleteArray_GsimRunData);
      instance.SetDestructor(&destruct_GsimRunData);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::GsimRunData*)
   {
      return GenerateInitInstanceLocal((::GsimRunData*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::GsimRunData*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
TClass *GsimRunData::fgIsA = 0;  // static to hold class pointer

//______________________________________________________________________________
const char *GsimRunData::Class_Name()
{
   return "GsimRunData";
}

//______________________________________________________________________________
const char *GsimRunData::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::GsimRunData*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int GsimRunData::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::GsimRunData*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
void GsimRunData::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::GsimRunData*)0x0)->GetClass();
}

//______________________________________________________________________________
TClass *GsimRunData::Class()
{
   if (!fgIsA) fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::GsimRunData*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
void GsimRunData::Streamer(TBuffer &R__b)
{
   // Stream an object of class GsimRunData.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(GsimRunData::Class(),this);
   } else {
      R__b.WriteClassBuffer(GsimRunData::Class(),this);
   }
}

//______________________________________________________________________________
void GsimRunData::ShowMembers(TMemberInspector &R__insp)
{
      // Inspect the data members of an object of class GsimRunData.
      TClass *R__cl = ::GsimRunData::IsA();
      if (R__cl || R__insp.IsA()) { }
      R__insp.Inspect(R__cl, R__insp.GetParent(), "runNumber", &runNumber);
      R__insp.Inspect(R__cl, R__insp.GetParent(), "runID", &runID);
      R__insp.Inspect(R__cl, R__insp.GetParent(), "nEventsRequested", &nEventsRequested);
      R__insp.Inspect(R__cl, R__insp.GetParent(), "nEventsProcessed", &nEventsProcessed);
      R__insp.Inspect(R__cl, R__insp.GetParent(), "nEventsStored", &nEventsStored);
      R__insp.Inspect(R__cl, R__insp.GetParent(), "version", &version);
      TObject::ShowMembers(R__insp);
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_GsimRunData(void *p) {
      return  p ? new(p) ::GsimRunData : new ::GsimRunData;
   }
   static void *newArray_GsimRunData(Long_t nElements, void *p) {
      return p ? new(p) ::GsimRunData[nElements] : new ::GsimRunData[nElements];
   }
   // Wrapper around operator delete
   static void delete_GsimRunData(void *p) {
      delete ((::GsimRunData*)p);
   }
   static void deleteArray_GsimRunData(void *p) {
      delete [] ((::GsimRunData*)p);
   }
   static void destruct_GsimRunData(void *p) {
      typedef ::GsimRunData current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::GsimRunData

/********************************************************
* src/GsimRunDataDict.cc
* CAUTION: DON'T CHANGE THIS FILE. THIS FILE IS AUTOMATICALLY GENERATED
*          FROM HEADER FILES LISTED IN G__setup_cpp_environmentXXX().
*          CHANGE THOSE HEADER FILES AND REGENERATE THIS FILE.
********************************************************/

#ifdef G__MEMTEST
#undef malloc
#undef free
#endif

#if defined(__GNUC__) && __GNUC__ >= 4 && ((__GNUC_MINOR__ == 2 && __GNUC_PATCHLEVEL__ >= 1) || (__GNUC_MINOR__ >= 3))
#pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif

extern "C" void G__cpp_reset_tagtableGsimRunDataDict();

extern "C" void G__set_cpp_environmentGsimRunDataDict() {
  G__add_compiledheader("TObject.h");
  G__add_compiledheader("TMemberInspector.h");
  G__add_compiledheader("./GsimData/GsimRunData.h");
  G__cpp_reset_tagtableGsimRunDataDict();
}
#include <new>
extern "C" int G__cpp_dllrevGsimRunDataDict() { return(30051515); }

/*********************************************************
* Member function Interface Method
*********************************************************/

/* GsimRunData */
static int G__GsimRunDataDict_162_0_1(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
   GsimRunData* p = NULL;
   char* gvp = (char*) G__getgvp();
   int n = G__getaryconstruct();
   if (n) {
     if ((gvp == (char*)G__PVOID) || (gvp == 0)) {
       p = new GsimRunData[n];
     } else {
       p = new((void*) gvp) GsimRunData[n];
     }
   } else {
     if ((gvp == (char*)G__PVOID) || (gvp == 0)) {
       p = new GsimRunData;
     } else {
       p = new((void*) gvp) GsimRunData;
     }
   }
   result7->obj.i = (long) p;
   result7->ref = (long) p;
   G__set_tagnum(result7,G__get_linked_tagnum(&G__GsimRunDataDictLN_GsimRunData));
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GsimRunDataDict_162_0_3(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      ((GsimRunData*) G__getstructoffset())->initializeDataValues();
      G__setnull(result7);
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GsimRunDataDict_162_0_4(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 85, (long) GsimRunData::Class());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GsimRunDataDict_162_0_5(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 67, (long) GsimRunData::Class_Name());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GsimRunDataDict_162_0_6(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 115, (long) GsimRunData::Class_Version());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GsimRunDataDict_162_0_7(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      GsimRunData::Dictionary();
      G__setnull(result7);
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GsimRunDataDict_162_0_11(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      ((GsimRunData*) G__getstructoffset())->StreamerNVirtual(*(TBuffer*) libp->para[0].ref);
      G__setnull(result7);
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GsimRunDataDict_162_0_12(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 67, (long) GsimRunData::DeclFileName());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GsimRunDataDict_162_0_13(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 105, (long) GsimRunData::ImplFileLine());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GsimRunDataDict_162_0_14(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 67, (long) GsimRunData::ImplFileName());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GsimRunDataDict_162_0_15(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 105, (long) GsimRunData::DeclFileLine());
   return(1 || funcname || hash || result7 || libp) ;
}

// automatic copy constructor
static int G__GsimRunDataDict_162_0_16(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)

{
   GsimRunData* p;
   void* tmp = (void*) G__int(libp->para[0]);
   p = new GsimRunData(*(GsimRunData*) tmp);
   result7->obj.i = (long) p;
   result7->ref = (long) p;
   G__set_tagnum(result7,G__get_linked_tagnum(&G__GsimRunDataDictLN_GsimRunData));
   return(1 || funcname || hash || result7 || libp) ;
}

// automatic destructor
typedef GsimRunData G__TGsimRunData;
static int G__GsimRunDataDict_162_0_17(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
   char* gvp = (char*) G__getgvp();
   long soff = G__getstructoffset();
   int n = G__getaryconstruct();
   //
   //has_a_delete: 1
   //has_own_delete1arg: 0
   //has_own_delete2arg: 0
   //
   if (!soff) {
     return(1);
   }
   if (n) {
     if (gvp == (char*)G__PVOID) {
       delete[] (GsimRunData*) soff;
     } else {
       G__setgvp((long) G__PVOID);
       for (int i = n - 1; i >= 0; --i) {
         ((GsimRunData*) (soff+(sizeof(GsimRunData)*i)))->~G__TGsimRunData();
       }
       G__setgvp((long)gvp);
     }
   } else {
     if (gvp == (char*)G__PVOID) {
       delete (GsimRunData*) soff;
     } else {
       G__setgvp((long) G__PVOID);
       ((GsimRunData*) (soff))->~G__TGsimRunData();
       G__setgvp((long)gvp);
     }
   }
   G__setnull(result7);
   return(1 || funcname || hash || result7 || libp) ;
}

// automatic assignment operator
static int G__GsimRunDataDict_162_0_18(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
   GsimRunData* dest = (GsimRunData*) G__getstructoffset();
   *dest = *(GsimRunData*) libp->para[0].ref;
   const GsimRunData& obj = *dest;
   result7->ref = (long) (&obj);
   result7->obj.i = (long) (&obj);
   return(1 || funcname || hash || result7 || libp) ;
}


/* Setting up global function */

/*********************************************************
* Member function Stub
*********************************************************/

/* GsimRunData */

/*********************************************************
* Global function Stub
*********************************************************/

/*********************************************************
* Get size of pointer to member function
*********************************************************/
class G__Sizep2memfuncGsimRunDataDict {
 public:
  G__Sizep2memfuncGsimRunDataDict(): p(&G__Sizep2memfuncGsimRunDataDict::sizep2memfunc) {}
    size_t sizep2memfunc() { return(sizeof(p)); }
  private:
    size_t (G__Sizep2memfuncGsimRunDataDict::*p)();
};

size_t G__get_sizep2memfuncGsimRunDataDict()
{
  G__Sizep2memfuncGsimRunDataDict a;
  G__setsizep2memfunc((int)a.sizep2memfunc());
  return((size_t)a.sizep2memfunc());
}


/*********************************************************
* virtual base class offset calculation interface
*********************************************************/

   /* Setting up class inheritance */

/*********************************************************
* Inheritance information setup/
*********************************************************/
extern "C" void G__cpp_setup_inheritanceGsimRunDataDict() {

   /* Setting up class inheritance */
   if(0==G__getnumbaseclass(G__get_linked_tagnum(&G__GsimRunDataDictLN_GsimRunData))) {
     GsimRunData *G__Lderived;
     G__Lderived=(GsimRunData*)0x1000;
     {
       TObject *G__Lpbase=(TObject*)G__Lderived;
       G__inheritance_setup(G__get_linked_tagnum(&G__GsimRunDataDictLN_GsimRunData),G__get_linked_tagnum(&G__GsimRunDataDictLN_TObject),(long)G__Lpbase-(long)G__Lderived,1,1);
     }
   }
}

/*********************************************************
* typedef information setup/
*********************************************************/
extern "C" void G__cpp_setup_typetableGsimRunDataDict() {

   /* Setting up typedef entry */
   G__search_typename2("Version_t",115,-1,0,-1);
   G__setnewtype(-1,"Class version identifier (short)",0);
   G__search_typename2("vector<ROOT::TSchemaHelper>",117,G__get_linked_tagnum(&G__GsimRunDataDictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("reverse_iterator<const_iterator>",117,G__get_linked_tagnum(&G__GsimRunDataDictLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR),0,G__get_linked_tagnum(&G__GsimRunDataDictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR));
   G__setnewtype(-1,NULL,0);
   G__search_typename2("reverse_iterator<iterator>",117,G__get_linked_tagnum(&G__GsimRunDataDictLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR),0,G__get_linked_tagnum(&G__GsimRunDataDictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR));
   G__setnewtype(-1,NULL,0);
   G__search_typename2("vector<TVirtualArray*>",117,G__get_linked_tagnum(&G__GsimRunDataDictLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("reverse_iterator<const_iterator>",117,G__get_linked_tagnum(&G__GsimRunDataDictLN_reverse_iteratorlEvectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgRcLcLiteratorgR),0,G__get_linked_tagnum(&G__GsimRunDataDictLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR));
   G__setnewtype(-1,NULL,0);
   G__search_typename2("reverse_iterator<iterator>",117,G__get_linked_tagnum(&G__GsimRunDataDictLN_reverse_iteratorlEvectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgRcLcLiteratorgR),0,G__get_linked_tagnum(&G__GsimRunDataDictLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR));
   G__setnewtype(-1,NULL,0);
}

/*********************************************************
* Data Member information setup/
*********************************************************/

   /* Setting up class,struct,union tag member variable */

   /* GsimRunData */
static void G__setup_memvarGsimRunData(void) {
   G__tag_memvar_setup(G__get_linked_tagnum(&G__GsimRunDataDictLN_GsimRunData));
   { GsimRunData *p; p=(GsimRunData*)0x1000; if (p) { }
   G__memvar_setup((void*)((long)(&p->runNumber)-(long)(p)),114,0,0,-1,G__defined_typename("UShort_t"),-1,1,"runNumber=",0,(char*)NULL);
   G__memvar_setup((void*)((long)(&p->runID)-(long)(p)),114,0,0,-1,G__defined_typename("UShort_t"),-1,1,"runID=",0,(char*)NULL);
   G__memvar_setup((void*)((long)(&p->nEventsRequested)-(long)(p)),104,0,0,-1,G__defined_typename("UInt_t"),-1,1,"nEventsRequested=",0,(char*)NULL);
   G__memvar_setup((void*)((long)(&p->nEventsProcessed)-(long)(p)),104,0,0,-1,G__defined_typename("UInt_t"),-1,1,"nEventsProcessed=",0,(char*)NULL);
   G__memvar_setup((void*)((long)(&p->nEventsStored)-(long)(p)),104,0,0,-1,G__defined_typename("UInt_t"),-1,1,"nEventsStored=",0,(char*)NULL);
   G__memvar_setup((void*)((long)(&p->version)-(long)(p)),104,0,0,-1,G__defined_typename("UInt_t"),-1,1,"version=",0,(char*)NULL);
   G__memvar_setup((void*)0,85,0,0,G__get_linked_tagnum(&G__GsimRunDataDictLN_TClass),-1,-2,4,"fgIsA=",0,(char*)NULL);
   }
   G__tag_memvar_reset();
}

extern "C" void G__cpp_setup_memvarGsimRunDataDict() {
}
/***********************************************************
************************************************************
************************************************************
************************************************************
************************************************************
************************************************************
************************************************************
***********************************************************/

/*********************************************************
* Member function information setup for each class
*********************************************************/
static void G__setup_memfuncGsimRunData(void) {
   /* GsimRunData */
   G__tag_memfunc_setup(G__get_linked_tagnum(&G__GsimRunDataDictLN_GsimRunData));
   G__memfunc_setup("GsimRunData",1087,G__GsimRunDataDict_162_0_1, 105, G__get_linked_tagnum(&G__GsimRunDataDictLN_GsimRunData), -1, 0, 0, 1, 1, 0, "", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("Clear",487,(G__InterfaceMethod) NULL,121, -1, -1, 0, 1, 1, 1, 0, "C - 'Option_t' 10 '\"\"' opt", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("initializeDataValues",2076,G__GsimRunDataDict_162_0_3, 121, -1, -1, 0, 0, 1, 1, 0, "", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("Class",502,G__GsimRunDataDict_162_0_4, 85, G__get_linked_tagnum(&G__GsimRunDataDictLN_TClass), -1, 0, 0, 3, 1, 0, "", (char*)NULL, (void*) G__func2void( (TClass* (*)())(&GsimRunData::Class) ), 0);
   G__memfunc_setup("Class_Name",982,G__GsimRunDataDict_162_0_5, 67, -1, -1, 0, 0, 3, 1, 1, "", (char*)NULL, (void*) G__func2void( (const char* (*)())(&GsimRunData::Class_Name) ), 0);
   G__memfunc_setup("Class_Version",1339,G__GsimRunDataDict_162_0_6, 115, -1, G__defined_typename("Version_t"), 0, 0, 3, 1, 0, "", (char*)NULL, (void*) G__func2void( (Version_t (*)())(&GsimRunData::Class_Version) ), 0);
   G__memfunc_setup("Dictionary",1046,G__GsimRunDataDict_162_0_7, 121, -1, -1, 0, 0, 3, 1, 0, "", (char*)NULL, (void*) G__func2void( (void (*)())(&GsimRunData::Dictionary) ), 0);
   G__memfunc_setup("IsA",253,(G__InterfaceMethod) NULL,85, G__get_linked_tagnum(&G__GsimRunDataDictLN_TClass), -1, 0, 0, 1, 1, 8, "", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("ShowMembers",1132,(G__InterfaceMethod) NULL,121, -1, -1, 0, 1, 1, 1, 0, "u 'TMemberInspector' - 1 - insp", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("Streamer",835,(G__InterfaceMethod) NULL,121, -1, -1, 0, 1, 1, 1, 0, "u 'TBuffer' - 1 - b", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("StreamerNVirtual",1656,G__GsimRunDataDict_162_0_11, 121, -1, -1, 0, 1, 1, 1, 0, "u 'TBuffer' - 1 - b", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("DeclFileName",1145,G__GsimRunDataDict_162_0_12, 67, -1, -1, 0, 0, 3, 1, 1, "", (char*)NULL, (void*) G__func2void( (const char* (*)())(&GsimRunData::DeclFileName) ), 0);
   G__memfunc_setup("ImplFileLine",1178,G__GsimRunDataDict_162_0_13, 105, -1, -1, 0, 0, 3, 1, 0, "", (char*)NULL, (void*) G__func2void( (int (*)())(&GsimRunData::ImplFileLine) ), 0);
   G__memfunc_setup("ImplFileName",1171,G__GsimRunDataDict_162_0_14, 67, -1, -1, 0, 0, 3, 1, 1, "", (char*)NULL, (void*) G__func2void( (const char* (*)())(&GsimRunData::ImplFileName) ), 0);
   G__memfunc_setup("DeclFileLine",1152,G__GsimRunDataDict_162_0_15, 105, -1, -1, 0, 0, 3, 1, 0, "", (char*)NULL, (void*) G__func2void( (int (*)())(&GsimRunData::DeclFileLine) ), 0);
   // automatic copy constructor
   G__memfunc_setup("GsimRunData", 1087, G__GsimRunDataDict_162_0_16, (int) ('i'), G__get_linked_tagnum(&G__GsimRunDataDictLN_GsimRunData), -1, 0, 1, 1, 1, 0, "u 'GsimRunData' - 11 - -", (char*) NULL, (void*) NULL, 0);
   // automatic destructor
   G__memfunc_setup("~GsimRunData", 1213, G__GsimRunDataDict_162_0_17, (int) ('y'), -1, -1, 0, 0, 1, 1, 0, "", (char*) NULL, (void*) NULL, 1);
   // automatic assignment operator
   G__memfunc_setup("operator=", 937, G__GsimRunDataDict_162_0_18, (int) ('u'), G__get_linked_tagnum(&G__GsimRunDataDictLN_GsimRunData), -1, 1, 1, 1, 1, 0, "u 'GsimRunData' - 11 - -", (char*) NULL, (void*) NULL, 0);
   G__tag_memfunc_reset();
}


/*********************************************************
* Member function information setup
*********************************************************/
extern "C" void G__cpp_setup_memfuncGsimRunDataDict() {
}

/*********************************************************
* Global variable information setup for each class
*********************************************************/
static void G__cpp_setup_global0() {

   /* Setting up global variables */
   G__resetplocal();

}

static void G__cpp_setup_global1() {

   G__resetglobalenv();
}
extern "C" void G__cpp_setup_globalGsimRunDataDict() {
  G__cpp_setup_global0();
  G__cpp_setup_global1();
}

/*********************************************************
* Global function information setup for each class
*********************************************************/
static void G__cpp_setup_func0() {
   G__lastifuncposition();

}

static void G__cpp_setup_func1() {
}

static void G__cpp_setup_func2() {
}

static void G__cpp_setup_func3() {
}

static void G__cpp_setup_func4() {
}

static void G__cpp_setup_func5() {
}

static void G__cpp_setup_func6() {
}

static void G__cpp_setup_func7() {
}

static void G__cpp_setup_func8() {
}

static void G__cpp_setup_func9() {
}

static void G__cpp_setup_func10() {
}

static void G__cpp_setup_func11() {
}

static void G__cpp_setup_func12() {

   G__resetifuncposition();
}

extern "C" void G__cpp_setup_funcGsimRunDataDict() {
  G__cpp_setup_func0();
  G__cpp_setup_func1();
  G__cpp_setup_func2();
  G__cpp_setup_func3();
  G__cpp_setup_func4();
  G__cpp_setup_func5();
  G__cpp_setup_func6();
  G__cpp_setup_func7();
  G__cpp_setup_func8();
  G__cpp_setup_func9();
  G__cpp_setup_func10();
  G__cpp_setup_func11();
  G__cpp_setup_func12();
}

/*********************************************************
* Class,struct,union,enum tag information setup
*********************************************************/
/* Setup class/struct taginfo */
G__linked_taginfo G__GsimRunDataDictLN_TClass = { "TClass" , 99 , -1 };
G__linked_taginfo G__GsimRunDataDictLN_TBuffer = { "TBuffer" , 99 , -1 };
G__linked_taginfo G__GsimRunDataDictLN_TMemberInspector = { "TMemberInspector" , 99 , -1 };
G__linked_taginfo G__GsimRunDataDictLN_TObject = { "TObject" , 99 , -1 };
G__linked_taginfo G__GsimRunDataDictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR = { "vector<ROOT::TSchemaHelper,allocator<ROOT::TSchemaHelper> >" , 99 , -1 };
G__linked_taginfo G__GsimRunDataDictLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR = { "reverse_iterator<vector<ROOT::TSchemaHelper,allocator<ROOT::TSchemaHelper> >::iterator>" , 99 , -1 };
G__linked_taginfo G__GsimRunDataDictLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR = { "vector<TVirtualArray*,allocator<TVirtualArray*> >" , 99 , -1 };
G__linked_taginfo G__GsimRunDataDictLN_reverse_iteratorlEvectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgRcLcLiteratorgR = { "reverse_iterator<vector<TVirtualArray*,allocator<TVirtualArray*> >::iterator>" , 99 , -1 };
G__linked_taginfo G__GsimRunDataDictLN_GsimRunData = { "GsimRunData" , 99 , -1 };

/* Reset class/struct taginfo */
extern "C" void G__cpp_reset_tagtableGsimRunDataDict() {
  G__GsimRunDataDictLN_TClass.tagnum = -1 ;
  G__GsimRunDataDictLN_TBuffer.tagnum = -1 ;
  G__GsimRunDataDictLN_TMemberInspector.tagnum = -1 ;
  G__GsimRunDataDictLN_TObject.tagnum = -1 ;
  G__GsimRunDataDictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR.tagnum = -1 ;
  G__GsimRunDataDictLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR.tagnum = -1 ;
  G__GsimRunDataDictLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR.tagnum = -1 ;
  G__GsimRunDataDictLN_reverse_iteratorlEvectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgRcLcLiteratorgR.tagnum = -1 ;
  G__GsimRunDataDictLN_GsimRunData.tagnum = -1 ;
}


extern "C" void G__cpp_setup_tagtableGsimRunDataDict() {

   /* Setting up class,struct,union tag entry */
   G__get_linked_tagnum_fwd(&G__GsimRunDataDictLN_TClass);
   G__get_linked_tagnum_fwd(&G__GsimRunDataDictLN_TBuffer);
   G__get_linked_tagnum_fwd(&G__GsimRunDataDictLN_TMemberInspector);
   G__get_linked_tagnum_fwd(&G__GsimRunDataDictLN_TObject);
   G__get_linked_tagnum_fwd(&G__GsimRunDataDictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR);
   G__get_linked_tagnum_fwd(&G__GsimRunDataDictLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR);
   G__get_linked_tagnum_fwd(&G__GsimRunDataDictLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR);
   G__get_linked_tagnum_fwd(&G__GsimRunDataDictLN_reverse_iteratorlEvectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgRcLcLiteratorgR);
   G__tagtable_setup(G__get_linked_tagnum_fwd(&G__GsimRunDataDictLN_GsimRunData),sizeof(GsimRunData),-1,292096,(char*)NULL,G__setup_memvarGsimRunData,G__setup_memfuncGsimRunData);
}
extern "C" void G__cpp_setupGsimRunDataDict(void) {
  G__check_setup_version(30051515,"G__cpp_setupGsimRunDataDict()");
  G__set_cpp_environmentGsimRunDataDict();
  G__cpp_setup_tagtableGsimRunDataDict();

  G__cpp_setup_inheritanceGsimRunDataDict();

  G__cpp_setup_typetableGsimRunDataDict();

  G__cpp_setup_memvarGsimRunDataDict();

  G__cpp_setup_memfuncGsimRunDataDict();
  G__cpp_setup_globalGsimRunDataDict();
  G__cpp_setup_funcGsimRunDataDict();

   if(0==G__getsizep2memfunc()) G__get_sizep2memfuncGsimRunDataDict();
  return;
}
class G__cpp_setup_initGsimRunDataDict {
  public:
    G__cpp_setup_initGsimRunDataDict() { G__add_setup_func("GsimRunDataDict",(G__incsetup)(&G__cpp_setupGsimRunDataDict)); G__call_setup_funcs(); }
   ~G__cpp_setup_initGsimRunDataDict() { G__remove_setup_func("GsimRunDataDict"); }
};
G__cpp_setup_initGsimRunDataDict G__cpp_setup_initializerGsimRunDataDict;

