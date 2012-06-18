//
// File generated by rootcint at Sun Jun  3 02:38:16 2012

// Do NOT change. Changes will be lost next time file is generated
//

#define R__DICTIONARY_FILENAME srcdIGsimRandDataDict
#include "RConfig.h" //rootcint 4834
#if !defined(R__ACCESS_IN_SYMBOL)
//Break the privacy of classes -- Disabled for the moment
#define private public
#define protected public
#endif

// Since CINT ignores the std namespace, we need to do so in this file.
namespace std {} using namespace std;
#include "GsimRandDataDict.h"

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
   void GsimRandData_ShowMembers(void *obj, TMemberInspector &R__insp);
   static void *new_GsimRandData(void *p = 0);
   static void *newArray_GsimRandData(Long_t size, void *p);
   static void delete_GsimRandData(void *p);
   static void deleteArray_GsimRandData(void *p);
   static void destruct_GsimRandData(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::GsimRandData*)
   {
      ::GsimRandData *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::GsimRandData >(0);
      static ::ROOT::TGenericClassInfo 
         instance("GsimRandData", ::GsimRandData::Class_Version(), "././GsimData/GsimRandData.h", 30,
                  typeid(::GsimRandData), DefineBehavior(ptr, ptr),
                  &::GsimRandData::Dictionary, isa_proxy, 4,
                  sizeof(::GsimRandData) );
      instance.SetNew(&new_GsimRandData);
      instance.SetNewArray(&newArray_GsimRandData);
      instance.SetDelete(&delete_GsimRandData);
      instance.SetDeleteArray(&deleteArray_GsimRandData);
      instance.SetDestructor(&destruct_GsimRandData);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::GsimRandData*)
   {
      return GenerateInitInstanceLocal((::GsimRandData*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::GsimRandData*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
TClass *GsimRandData::fgIsA = 0;  // static to hold class pointer

//______________________________________________________________________________
const char *GsimRandData::Class_Name()
{
   return "GsimRandData";
}

//______________________________________________________________________________
const char *GsimRandData::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::GsimRandData*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int GsimRandData::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::GsimRandData*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
void GsimRandData::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::GsimRandData*)0x0)->GetClass();
}

//______________________________________________________________________________
TClass *GsimRandData::Class()
{
   if (!fgIsA) fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::GsimRandData*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
void GsimRandData::Streamer(TBuffer &R__b)
{
   // Stream an object of class GsimRandData.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(GsimRandData::Class(),this);
   } else {
      R__b.WriteClassBuffer(GsimRandData::Class(),this);
   }
}

//______________________________________________________________________________
void GsimRandData::ShowMembers(TMemberInspector &R__insp)
{
      // Inspect the data members of an object of class GsimRandData.
      TClass *R__cl = ::GsimRandData::IsA();
      if (R__cl || R__insp.IsA()) { }
      R__insp.Inspect(R__cl, R__insp.GetParent(), "run_number", &run_number);
      R__insp.Inspect(R__cl, R__insp.GetParent(), "event_number", &event_number);
      R__insp.Inspect(R__cl, R__insp.GetParent(), "engineID", &engineID);
      R__insp.Inspect(R__cl, R__insp.GetParent(), "seed[624]", seed);
      R__insp.Inspect(R__cl, R__insp.GetParent(), "count", &count);
      R__insp.Inspect(R__cl, R__insp.GetParent(), "version", &version);
      R__insp.Inspect(R__cl, R__insp.GetParent(), "name", (void*)&name);
      R__insp.InspectMember("string", (void*)&name, "name.", true);
      R__insp.Inspect(R__cl, R__insp.GetParent(), "className", (void*)&className);
      R__insp.InspectMember("string", (void*)&className, "className.", true);
      TObject::ShowMembers(R__insp);
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_GsimRandData(void *p) {
      return  p ? new(p) ::GsimRandData : new ::GsimRandData;
   }
   static void *newArray_GsimRandData(Long_t nElements, void *p) {
      return p ? new(p) ::GsimRandData[nElements] : new ::GsimRandData[nElements];
   }
   // Wrapper around operator delete
   static void delete_GsimRandData(void *p) {
      delete ((::GsimRandData*)p);
   }
   static void deleteArray_GsimRandData(void *p) {
      delete [] ((::GsimRandData*)p);
   }
   static void destruct_GsimRandData(void *p) {
      typedef ::GsimRandData current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::GsimRandData

/********************************************************
* src/GsimRandDataDict.cc
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

extern "C" void G__cpp_reset_tagtableGsimRandDataDict();

extern "C" void G__set_cpp_environmentGsimRandDataDict() {
  G__add_compiledheader("TObject.h");
  G__add_compiledheader("TMemberInspector.h");
  G__add_compiledheader("./GsimData/GsimRandData.h");
  G__cpp_reset_tagtableGsimRandDataDict();
}
#include <new>
extern "C" int G__cpp_dllrevGsimRandDataDict() { return(30051515); }

/*********************************************************
* Member function Interface Method
*********************************************************/

/* GsimRandData */
static int G__GsimRandDataDict_162_0_1(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
   GsimRandData* p = NULL;
   char* gvp = (char*) G__getgvp();
   int n = G__getaryconstruct();
   if (n) {
     if ((gvp == (char*)G__PVOID) || (gvp == 0)) {
       p = new GsimRandData[n];
     } else {
       p = new((void*) gvp) GsimRandData[n];
     }
   } else {
     if ((gvp == (char*)G__PVOID) || (gvp == 0)) {
       p = new GsimRandData;
     } else {
       p = new((void*) gvp) GsimRandData;
     }
   }
   result7->obj.i = (long) p;
   result7->ref = (long) p;
   G__set_tagnum(result7,G__get_linked_tagnum(&G__GsimRandDataDictLN_GsimRandData));
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GsimRandDataDict_162_0_3(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      ((GsimRandData*) G__getstructoffset())->initializeDataValues();
      G__setnull(result7);
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GsimRandDataDict_162_0_4(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 103, (long) GsimRandData::getSeed(*((string*) G__int(libp->para[0])), (int) G__int(libp->para[1])
, (int) G__int(libp->para[2]), *(vector<unsigned long>*) libp->para[3].ref));
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GsimRandDataDict_162_0_5(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      {
         string* pobj;
         string xobj = ((GsimRandData*) G__getstructoffset())->getClassName();
         pobj = new string(xobj);
         result7->obj.i = (long) ((void*) pobj);
         result7->ref = result7->obj.i;
         G__store_tempobject(*result7);
      }
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GsimRandDataDict_162_0_6(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 85, (long) GsimRandData::Class());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GsimRandDataDict_162_0_7(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 67, (long) GsimRandData::Class_Name());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GsimRandDataDict_162_0_8(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 115, (long) GsimRandData::Class_Version());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GsimRandDataDict_162_0_9(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      GsimRandData::Dictionary();
      G__setnull(result7);
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GsimRandDataDict_162_0_13(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      ((GsimRandData*) G__getstructoffset())->StreamerNVirtual(*(TBuffer*) libp->para[0].ref);
      G__setnull(result7);
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GsimRandDataDict_162_0_14(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 67, (long) GsimRandData::DeclFileName());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GsimRandDataDict_162_0_15(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 105, (long) GsimRandData::ImplFileLine());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GsimRandDataDict_162_0_16(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 67, (long) GsimRandData::ImplFileName());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GsimRandDataDict_162_0_17(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 105, (long) GsimRandData::DeclFileLine());
   return(1 || funcname || hash || result7 || libp) ;
}

// automatic copy constructor
static int G__GsimRandDataDict_162_0_18(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)

{
   GsimRandData* p;
   void* tmp = (void*) G__int(libp->para[0]);
   p = new GsimRandData(*(GsimRandData*) tmp);
   result7->obj.i = (long) p;
   result7->ref = (long) p;
   G__set_tagnum(result7,G__get_linked_tagnum(&G__GsimRandDataDictLN_GsimRandData));
   return(1 || funcname || hash || result7 || libp) ;
}

// automatic destructor
typedef GsimRandData G__TGsimRandData;
static int G__GsimRandDataDict_162_0_19(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
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
       delete[] (GsimRandData*) soff;
     } else {
       G__setgvp((long) G__PVOID);
       for (int i = n - 1; i >= 0; --i) {
         ((GsimRandData*) (soff+(sizeof(GsimRandData)*i)))->~G__TGsimRandData();
       }
       G__setgvp((long)gvp);
     }
   } else {
     if (gvp == (char*)G__PVOID) {
       delete (GsimRandData*) soff;
     } else {
       G__setgvp((long) G__PVOID);
       ((GsimRandData*) (soff))->~G__TGsimRandData();
       G__setgvp((long)gvp);
     }
   }
   G__setnull(result7);
   return(1 || funcname || hash || result7 || libp) ;
}

// automatic assignment operator
static int G__GsimRandDataDict_162_0_20(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
   GsimRandData* dest = (GsimRandData*) G__getstructoffset();
   *dest = *(GsimRandData*) libp->para[0].ref;
   const GsimRandData& obj = *dest;
   result7->ref = (long) (&obj);
   result7->obj.i = (long) (&obj);
   return(1 || funcname || hash || result7 || libp) ;
}


/* Setting up global function */

/*********************************************************
* Member function Stub
*********************************************************/

/* GsimRandData */

/*********************************************************
* Global function Stub
*********************************************************/

/*********************************************************
* Get size of pointer to member function
*********************************************************/
class G__Sizep2memfuncGsimRandDataDict {
 public:
  G__Sizep2memfuncGsimRandDataDict(): p(&G__Sizep2memfuncGsimRandDataDict::sizep2memfunc) {}
    size_t sizep2memfunc() { return(sizeof(p)); }
  private:
    size_t (G__Sizep2memfuncGsimRandDataDict::*p)();
};

size_t G__get_sizep2memfuncGsimRandDataDict()
{
  G__Sizep2memfuncGsimRandDataDict a;
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
extern "C" void G__cpp_setup_inheritanceGsimRandDataDict() {

   /* Setting up class inheritance */
   if(0==G__getnumbaseclass(G__get_linked_tagnum(&G__GsimRandDataDictLN_GsimRandData))) {
     GsimRandData *G__Lderived;
     G__Lderived=(GsimRandData*)0x1000;
     {
       TObject *G__Lpbase=(TObject*)G__Lderived;
       G__inheritance_setup(G__get_linked_tagnum(&G__GsimRandDataDictLN_GsimRandData),G__get_linked_tagnum(&G__GsimRandDataDictLN_TObject),(long)G__Lpbase-(long)G__Lderived,1,1);
     }
   }
}

/*********************************************************
* typedef information setup/
*********************************************************/
extern "C" void G__cpp_setup_typetableGsimRandDataDict() {

   /* Setting up typedef entry */
   G__search_typename2("Version_t",115,-1,0,-1);
   G__setnewtype(-1,"Class version identifier (short)",0);
   G__search_typename2("vector<ROOT::TSchemaHelper>",117,G__get_linked_tagnum(&G__GsimRandDataDictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("reverse_iterator<const_iterator>",117,G__get_linked_tagnum(&G__GsimRandDataDictLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR),0,G__get_linked_tagnum(&G__GsimRandDataDictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR));
   G__setnewtype(-1,NULL,0);
   G__search_typename2("reverse_iterator<iterator>",117,G__get_linked_tagnum(&G__GsimRandDataDictLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR),0,G__get_linked_tagnum(&G__GsimRandDataDictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR));
   G__setnewtype(-1,NULL,0);
   G__search_typename2("vector<TVirtualArray*>",117,G__get_linked_tagnum(&G__GsimRandDataDictLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("reverse_iterator<const_iterator>",117,G__get_linked_tagnum(&G__GsimRandDataDictLN_reverse_iteratorlEvectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgRcLcLiteratorgR),0,G__get_linked_tagnum(&G__GsimRandDataDictLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR));
   G__setnewtype(-1,NULL,0);
   G__search_typename2("reverse_iterator<iterator>",117,G__get_linked_tagnum(&G__GsimRandDataDictLN_reverse_iteratorlEvectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgRcLcLiteratorgR),0,G__get_linked_tagnum(&G__GsimRandDataDictLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR));
   G__setnewtype(-1,NULL,0);
}

/*********************************************************
* Data Member information setup/
*********************************************************/

   /* Setting up class,struct,union tag member variable */

   /* GsimRandData */
static void G__setup_memvarGsimRandData(void) {
   G__tag_memvar_setup(G__get_linked_tagnum(&G__GsimRandDataDictLN_GsimRandData));
   { GsimRandData *p; p=(GsimRandData*)0x1000; if (p) { }
   G__memvar_setup((void*)((long)(&p->run_number)-(long)(p)),114,0,0,-1,G__defined_typename("UShort_t"),-1,1,"run_number=",0,(char*)NULL);
   G__memvar_setup((void*)((long)(&p->event_number)-(long)(p)),104,0,0,-1,G__defined_typename("UInt_t"),-1,1,"event_number=",0,(char*)NULL);
   G__memvar_setup((void*)((long)(&p->engineID)-(long)(p)),104,0,0,-1,G__defined_typename("UInt_t"),-1,1,"engineID=",0,(char*)NULL);
   G__memvar_setup((void*)((long)(&p->seed)-(long)(p)),104,0,0,-1,G__defined_typename("UInt_t"),-1,1,"seed[624]=",0,"[624]");
   G__memvar_setup((void*)((long)(&p->count)-(long)(p)),104,0,0,-1,G__defined_typename("UInt_t"),-1,1,"count=",0,(char*)NULL);
   G__memvar_setup((void*)((long)(&p->version)-(long)(p)),114,0,0,-1,G__defined_typename("UShort_t"),-1,1,"version=",0,(char*)NULL);
   G__memvar_setup((void*)0,117,0,0,G__get_linked_tagnum(&G__GsimRandDataDictLN_string),-1,-1,2,"name=",0,"!");
   G__memvar_setup((void*)0,117,0,0,G__get_linked_tagnum(&G__GsimRandDataDictLN_string),-1,-1,2,"className=",0,"!");
   G__memvar_setup((void*)0,85,0,0,G__get_linked_tagnum(&G__GsimRandDataDictLN_TClass),-1,-2,4,"fgIsA=",0,(char*)NULL);
   }
   G__tag_memvar_reset();
}

extern "C" void G__cpp_setup_memvarGsimRandDataDict() {
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
static void G__setup_memfuncGsimRandData(void) {
   /* GsimRandData */
   G__tag_memfunc_setup(G__get_linked_tagnum(&G__GsimRandDataDictLN_GsimRandData));
   G__memfunc_setup("GsimRandData",1167,G__GsimRandDataDict_162_0_1, 105, G__get_linked_tagnum(&G__GsimRandDataDictLN_GsimRandData), -1, 0, 0, 1, 1, 0, "", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("Clear",487,(G__InterfaceMethod) NULL,121, -1, -1, 0, 1, 1, 1, 0, "C - 'Option_t' 10 '\"\"' opt", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("initializeDataValues",2076,G__GsimRandDataDict_162_0_3, 121, -1, -1, 0, 0, 1, 1, 0, "", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("getSeed",705,G__GsimRandDataDict_162_0_4, 103, -1, -1, 0, 4, 3, 1, 0, 
"u 'string' - 0 - tfName i - - 0 - treeID "
"i - - 0 - eventID u 'vector<unsigned long,allocator<unsigned long> >' 'vector<unsigned long>' 1 - seedVector", (char*)NULL, (void*) G__func2void( (bool (*)(string, int, int, vector<unsigned long>&))(&GsimRandData::getSeed) ), 0);
   G__memfunc_setup("getClassName",1207,G__GsimRandDataDict_162_0_5, 117, G__get_linked_tagnum(&G__GsimRandDataDictLN_string), -1, 0, 0, 1, 1, 0, "", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("Class",502,G__GsimRandDataDict_162_0_6, 85, G__get_linked_tagnum(&G__GsimRandDataDictLN_TClass), -1, 0, 0, 3, 1, 0, "", (char*)NULL, (void*) G__func2void( (TClass* (*)())(&GsimRandData::Class) ), 0);
   G__memfunc_setup("Class_Name",982,G__GsimRandDataDict_162_0_7, 67, -1, -1, 0, 0, 3, 1, 1, "", (char*)NULL, (void*) G__func2void( (const char* (*)())(&GsimRandData::Class_Name) ), 0);
   G__memfunc_setup("Class_Version",1339,G__GsimRandDataDict_162_0_8, 115, -1, G__defined_typename("Version_t"), 0, 0, 3, 1, 0, "", (char*)NULL, (void*) G__func2void( (Version_t (*)())(&GsimRandData::Class_Version) ), 0);
   G__memfunc_setup("Dictionary",1046,G__GsimRandDataDict_162_0_9, 121, -1, -1, 0, 0, 3, 1, 0, "", (char*)NULL, (void*) G__func2void( (void (*)())(&GsimRandData::Dictionary) ), 0);
   G__memfunc_setup("IsA",253,(G__InterfaceMethod) NULL,85, G__get_linked_tagnum(&G__GsimRandDataDictLN_TClass), -1, 0, 0, 1, 1, 8, "", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("ShowMembers",1132,(G__InterfaceMethod) NULL,121, -1, -1, 0, 1, 1, 1, 0, "u 'TMemberInspector' - 1 - insp", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("Streamer",835,(G__InterfaceMethod) NULL,121, -1, -1, 0, 1, 1, 1, 0, "u 'TBuffer' - 1 - b", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("StreamerNVirtual",1656,G__GsimRandDataDict_162_0_13, 121, -1, -1, 0, 1, 1, 1, 0, "u 'TBuffer' - 1 - b", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("DeclFileName",1145,G__GsimRandDataDict_162_0_14, 67, -1, -1, 0, 0, 3, 1, 1, "", (char*)NULL, (void*) G__func2void( (const char* (*)())(&GsimRandData::DeclFileName) ), 0);
   G__memfunc_setup("ImplFileLine",1178,G__GsimRandDataDict_162_0_15, 105, -1, -1, 0, 0, 3, 1, 0, "", (char*)NULL, (void*) G__func2void( (int (*)())(&GsimRandData::ImplFileLine) ), 0);
   G__memfunc_setup("ImplFileName",1171,G__GsimRandDataDict_162_0_16, 67, -1, -1, 0, 0, 3, 1, 1, "", (char*)NULL, (void*) G__func2void( (const char* (*)())(&GsimRandData::ImplFileName) ), 0);
   G__memfunc_setup("DeclFileLine",1152,G__GsimRandDataDict_162_0_17, 105, -1, -1, 0, 0, 3, 1, 0, "", (char*)NULL, (void*) G__func2void( (int (*)())(&GsimRandData::DeclFileLine) ), 0);
   // automatic copy constructor
   G__memfunc_setup("GsimRandData", 1167, G__GsimRandDataDict_162_0_18, (int) ('i'), G__get_linked_tagnum(&G__GsimRandDataDictLN_GsimRandData), -1, 0, 1, 1, 1, 0, "u 'GsimRandData' - 11 - -", (char*) NULL, (void*) NULL, 0);
   // automatic destructor
   G__memfunc_setup("~GsimRandData", 1293, G__GsimRandDataDict_162_0_19, (int) ('y'), -1, -1, 0, 0, 1, 1, 0, "", (char*) NULL, (void*) NULL, 1);
   // automatic assignment operator
   G__memfunc_setup("operator=", 937, G__GsimRandDataDict_162_0_20, (int) ('u'), G__get_linked_tagnum(&G__GsimRandDataDictLN_GsimRandData), -1, 1, 1, 1, 1, 0, "u 'GsimRandData' - 11 - -", (char*) NULL, (void*) NULL, 0);
   G__tag_memfunc_reset();
}


/*********************************************************
* Member function information setup
*********************************************************/
extern "C" void G__cpp_setup_memfuncGsimRandDataDict() {
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
extern "C" void G__cpp_setup_globalGsimRandDataDict() {
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

extern "C" void G__cpp_setup_funcGsimRandDataDict() {
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
G__linked_taginfo G__GsimRandDataDictLN_TClass = { "TClass" , 99 , -1 };
G__linked_taginfo G__GsimRandDataDictLN_TBuffer = { "TBuffer" , 99 , -1 };
G__linked_taginfo G__GsimRandDataDictLN_TMemberInspector = { "TMemberInspector" , 99 , -1 };
G__linked_taginfo G__GsimRandDataDictLN_TObject = { "TObject" , 99 , -1 };
G__linked_taginfo G__GsimRandDataDictLN_vectorlEunsignedsPlongcOallocatorlEunsignedsPlonggRsPgR = { "vector<unsigned long,allocator<unsigned long> >" , 99 , -1 };
G__linked_taginfo G__GsimRandDataDictLN_string = { "string" , 99 , -1 };
G__linked_taginfo G__GsimRandDataDictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR = { "vector<ROOT::TSchemaHelper,allocator<ROOT::TSchemaHelper> >" , 99 , -1 };
G__linked_taginfo G__GsimRandDataDictLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR = { "reverse_iterator<vector<ROOT::TSchemaHelper,allocator<ROOT::TSchemaHelper> >::iterator>" , 99 , -1 };
G__linked_taginfo G__GsimRandDataDictLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR = { "vector<TVirtualArray*,allocator<TVirtualArray*> >" , 99 , -1 };
G__linked_taginfo G__GsimRandDataDictLN_reverse_iteratorlEvectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgRcLcLiteratorgR = { "reverse_iterator<vector<TVirtualArray*,allocator<TVirtualArray*> >::iterator>" , 99 , -1 };
G__linked_taginfo G__GsimRandDataDictLN_GsimRandData = { "GsimRandData" , 99 , -1 };

/* Reset class/struct taginfo */
extern "C" void G__cpp_reset_tagtableGsimRandDataDict() {
  G__GsimRandDataDictLN_TClass.tagnum = -1 ;
  G__GsimRandDataDictLN_TBuffer.tagnum = -1 ;
  G__GsimRandDataDictLN_TMemberInspector.tagnum = -1 ;
  G__GsimRandDataDictLN_TObject.tagnum = -1 ;
  G__GsimRandDataDictLN_vectorlEunsignedsPlongcOallocatorlEunsignedsPlonggRsPgR.tagnum = -1 ;
  G__GsimRandDataDictLN_string.tagnum = -1 ;
  G__GsimRandDataDictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR.tagnum = -1 ;
  G__GsimRandDataDictLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR.tagnum = -1 ;
  G__GsimRandDataDictLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR.tagnum = -1 ;
  G__GsimRandDataDictLN_reverse_iteratorlEvectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgRcLcLiteratorgR.tagnum = -1 ;
  G__GsimRandDataDictLN_GsimRandData.tagnum = -1 ;
}


extern "C" void G__cpp_setup_tagtableGsimRandDataDict() {

   /* Setting up class,struct,union tag entry */
   G__get_linked_tagnum_fwd(&G__GsimRandDataDictLN_TClass);
   G__get_linked_tagnum_fwd(&G__GsimRandDataDictLN_TBuffer);
   G__get_linked_tagnum_fwd(&G__GsimRandDataDictLN_TMemberInspector);
   G__get_linked_tagnum_fwd(&G__GsimRandDataDictLN_TObject);
   G__get_linked_tagnum_fwd(&G__GsimRandDataDictLN_vectorlEunsignedsPlongcOallocatorlEunsignedsPlonggRsPgR);
   G__get_linked_tagnum_fwd(&G__GsimRandDataDictLN_string);
   G__get_linked_tagnum_fwd(&G__GsimRandDataDictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR);
   G__get_linked_tagnum_fwd(&G__GsimRandDataDictLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR);
   G__get_linked_tagnum_fwd(&G__GsimRandDataDictLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR);
   G__get_linked_tagnum_fwd(&G__GsimRandDataDictLN_reverse_iteratorlEvectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgRcLcLiteratorgR);
   G__tagtable_setup(G__get_linked_tagnum_fwd(&G__GsimRandDataDictLN_GsimRandData),sizeof(GsimRandData),-1,292096,(char*)NULL,G__setup_memvarGsimRandData,G__setup_memfuncGsimRandData);
}
extern "C" void G__cpp_setupGsimRandDataDict(void) {
  G__check_setup_version(30051515,"G__cpp_setupGsimRandDataDict()");
  G__set_cpp_environmentGsimRandDataDict();
  G__cpp_setup_tagtableGsimRandDataDict();

  G__cpp_setup_inheritanceGsimRandDataDict();

  G__cpp_setup_typetableGsimRandDataDict();

  G__cpp_setup_memvarGsimRandDataDict();

  G__cpp_setup_memfuncGsimRandDataDict();
  G__cpp_setup_globalGsimRandDataDict();
  G__cpp_setup_funcGsimRandDataDict();

   if(0==G__getsizep2memfunc()) G__get_sizep2memfuncGsimRandDataDict();
  return;
}
class G__cpp_setup_initGsimRandDataDict {
  public:
    G__cpp_setup_initGsimRandDataDict() { G__add_setup_func("GsimRandDataDict",(G__incsetup)(&G__cpp_setupGsimRandDataDict)); G__call_setup_funcs(); }
   ~G__cpp_setup_initGsimRandDataDict() { G__remove_setup_func("GsimRandDataDict"); }
};
G__cpp_setup_initGsimRandDataDict G__cpp_setup_initializerGsimRandDataDict;

