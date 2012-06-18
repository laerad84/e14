//
// File generated by rootcint at Sun Jun  3 02:38:15 2012

// Do NOT change. Changes will be lost next time file is generated
//

#define R__DICTIONARY_FILENAME srcdIGsimDigiDataDict
#include "RConfig.h" //rootcint 4834
#if !defined(R__ACCESS_IN_SYMBOL)
//Break the privacy of classes -- Disabled for the moment
#define private public
#define protected public
#endif

// Since CINT ignores the std namespace, we need to do so in this file.
namespace std {} using namespace std;
#include "GsimDigiDataDict.h"

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
   void GsimDigiData_ShowMembers(void *obj, TMemberInspector &R__insp);
   static void *new_GsimDigiData(void *p = 0);
   static void *newArray_GsimDigiData(Long_t size, void *p);
   static void delete_GsimDigiData(void *p);
   static void deleteArray_GsimDigiData(void *p);
   static void destruct_GsimDigiData(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::GsimDigiData*)
   {
      ::GsimDigiData *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::GsimDigiData >(0);
      static ::ROOT::TGenericClassInfo 
         instance("GsimDigiData", ::GsimDigiData::Class_Version(), "././GsimData/GsimDigiData.h", 28,
                  typeid(::GsimDigiData), DefineBehavior(ptr, ptr),
                  &::GsimDigiData::Dictionary, isa_proxy, 4,
                  sizeof(::GsimDigiData) );
      instance.SetNew(&new_GsimDigiData);
      instance.SetNewArray(&newArray_GsimDigiData);
      instance.SetDelete(&delete_GsimDigiData);
      instance.SetDeleteArray(&deleteArray_GsimDigiData);
      instance.SetDestructor(&destruct_GsimDigiData);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::GsimDigiData*)
   {
      return GenerateInitInstanceLocal((::GsimDigiData*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::GsimDigiData*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
TClass *GsimDigiData::fgIsA = 0;  // static to hold class pointer

//______________________________________________________________________________
const char *GsimDigiData::Class_Name()
{
   return "GsimDigiData";
}

//______________________________________________________________________________
const char *GsimDigiData::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::GsimDigiData*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int GsimDigiData::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::GsimDigiData*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
void GsimDigiData::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::GsimDigiData*)0x0)->GetClass();
}

//______________________________________________________________________________
TClass *GsimDigiData::Class()
{
   if (!fgIsA) fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::GsimDigiData*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
void GsimDigiData::Streamer(TBuffer &R__b)
{
   // Stream an object of class GsimDigiData.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(GsimDigiData::Class(),this);
   } else {
      R__b.WriteClassBuffer(GsimDigiData::Class(),this);
   }
}

//______________________________________________________________________________
void GsimDigiData::ShowMembers(TMemberInspector &R__insp)
{
      // Inspect the data members of an object of class GsimDigiData.
      TClass *R__cl = ::GsimDigiData::IsA();
      if (R__cl || R__insp.IsA()) { }
      R__insp.Inspect(R__cl, R__insp.GetParent(), "detID", &detID);
      R__insp.Inspect(R__cl, R__insp.GetParent(), "modID", &modID);
      R__insp.Inspect(R__cl, R__insp.GetParent(), "energy", &energy);
      R__insp.Inspect(R__cl, R__insp.GetParent(), "time", &time);
      R__insp.Inspect(R__cl, R__insp.GetParent(), "thisID", &thisID);
      R__insp.Inspect(R__cl, R__insp.GetParent(), "status", &status);
      R__insp.Inspect(R__cl, R__insp.GetParent(), "track", &track);
      R__insp.Inspect(R__cl, R__insp.GetParent(), "mtimeEntry", &mtimeEntry);
      R__insp.Inspect(R__cl, R__insp.GetParent(), "mtimeSize", &mtimeSize);
      TObject::ShowMembers(R__insp);
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_GsimDigiData(void *p) {
      return  p ? new(p) ::GsimDigiData : new ::GsimDigiData;
   }
   static void *newArray_GsimDigiData(Long_t nElements, void *p) {
      return p ? new(p) ::GsimDigiData[nElements] : new ::GsimDigiData[nElements];
   }
   // Wrapper around operator delete
   static void delete_GsimDigiData(void *p) {
      delete ((::GsimDigiData*)p);
   }
   static void deleteArray_GsimDigiData(void *p) {
      delete [] ((::GsimDigiData*)p);
   }
   static void destruct_GsimDigiData(void *p) {
      typedef ::GsimDigiData current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::GsimDigiData

/********************************************************
* src/GsimDigiDataDict.cc
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

extern "C" void G__cpp_reset_tagtableGsimDigiDataDict();

extern "C" void G__set_cpp_environmentGsimDigiDataDict() {
  G__add_compiledheader("TObject.h");
  G__add_compiledheader("TMemberInspector.h");
  G__add_compiledheader("./GsimData/GsimDigiData.h");
  G__cpp_reset_tagtableGsimDigiDataDict();
}
#include <new>
extern "C" int G__cpp_dllrevGsimDigiDataDict() { return(30051515); }

/*********************************************************
* Member function Interface Method
*********************************************************/

/* GsimDigiData */
static int G__GsimDigiDataDict_162_0_1(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
   GsimDigiData* p = NULL;
   char* gvp = (char*) G__getgvp();
   int n = G__getaryconstruct();
   if (n) {
     if ((gvp == (char*)G__PVOID) || (gvp == 0)) {
       p = new GsimDigiData[n];
     } else {
       p = new((void*) gvp) GsimDigiData[n];
     }
   } else {
     if ((gvp == (char*)G__PVOID) || (gvp == 0)) {
       p = new GsimDigiData;
     } else {
       p = new((void*) gvp) GsimDigiData;
     }
   }
   result7->obj.i = (long) p;
   result7->ref = (long) p;
   G__set_tagnum(result7,G__get_linked_tagnum(&G__GsimDigiDataDictLN_GsimDigiData));
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GsimDigiDataDict_162_0_3(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      ((GsimDigiData*) G__getstructoffset())->initializeDataValues();
      G__setnull(result7);
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GsimDigiDataDict_162_0_4(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
   switch (libp->paran) {
   case 1:
      ((GsimDigiData*) G__getstructoffset())->dump((int) G__int(libp->para[0]));
      G__setnull(result7);
      break;
   case 0:
      ((GsimDigiData*) G__getstructoffset())->dump();
      G__setnull(result7);
      break;
   }
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GsimDigiDataDict_162_0_5(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 85, (long) GsimDigiData::Class());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GsimDigiDataDict_162_0_6(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 67, (long) GsimDigiData::Class_Name());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GsimDigiDataDict_162_0_7(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 115, (long) GsimDigiData::Class_Version());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GsimDigiDataDict_162_0_8(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      GsimDigiData::Dictionary();
      G__setnull(result7);
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GsimDigiDataDict_162_0_12(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      ((GsimDigiData*) G__getstructoffset())->StreamerNVirtual(*(TBuffer*) libp->para[0].ref);
      G__setnull(result7);
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GsimDigiDataDict_162_0_13(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 67, (long) GsimDigiData::DeclFileName());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GsimDigiDataDict_162_0_14(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 105, (long) GsimDigiData::ImplFileLine());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GsimDigiDataDict_162_0_15(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 67, (long) GsimDigiData::ImplFileName());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GsimDigiDataDict_162_0_16(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 105, (long) GsimDigiData::DeclFileLine());
   return(1 || funcname || hash || result7 || libp) ;
}

// automatic copy constructor
static int G__GsimDigiDataDict_162_0_17(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)

{
   GsimDigiData* p;
   void* tmp = (void*) G__int(libp->para[0]);
   p = new GsimDigiData(*(GsimDigiData*) tmp);
   result7->obj.i = (long) p;
   result7->ref = (long) p;
   G__set_tagnum(result7,G__get_linked_tagnum(&G__GsimDigiDataDictLN_GsimDigiData));
   return(1 || funcname || hash || result7 || libp) ;
}

// automatic destructor
typedef GsimDigiData G__TGsimDigiData;
static int G__GsimDigiDataDict_162_0_18(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
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
       delete[] (GsimDigiData*) soff;
     } else {
       G__setgvp((long) G__PVOID);
       for (int i = n - 1; i >= 0; --i) {
         ((GsimDigiData*) (soff+(sizeof(GsimDigiData)*i)))->~G__TGsimDigiData();
       }
       G__setgvp((long)gvp);
     }
   } else {
     if (gvp == (char*)G__PVOID) {
       delete (GsimDigiData*) soff;
     } else {
       G__setgvp((long) G__PVOID);
       ((GsimDigiData*) (soff))->~G__TGsimDigiData();
       G__setgvp((long)gvp);
     }
   }
   G__setnull(result7);
   return(1 || funcname || hash || result7 || libp) ;
}

// automatic assignment operator
static int G__GsimDigiDataDict_162_0_19(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
   GsimDigiData* dest = (GsimDigiData*) G__getstructoffset();
   *dest = *(GsimDigiData*) libp->para[0].ref;
   const GsimDigiData& obj = *dest;
   result7->ref = (long) (&obj);
   result7->obj.i = (long) (&obj);
   return(1 || funcname || hash || result7 || libp) ;
}


/* Setting up global function */

/*********************************************************
* Member function Stub
*********************************************************/

/* GsimDigiData */

/*********************************************************
* Global function Stub
*********************************************************/

/*********************************************************
* Get size of pointer to member function
*********************************************************/
class G__Sizep2memfuncGsimDigiDataDict {
 public:
  G__Sizep2memfuncGsimDigiDataDict(): p(&G__Sizep2memfuncGsimDigiDataDict::sizep2memfunc) {}
    size_t sizep2memfunc() { return(sizeof(p)); }
  private:
    size_t (G__Sizep2memfuncGsimDigiDataDict::*p)();
};

size_t G__get_sizep2memfuncGsimDigiDataDict()
{
  G__Sizep2memfuncGsimDigiDataDict a;
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
extern "C" void G__cpp_setup_inheritanceGsimDigiDataDict() {

   /* Setting up class inheritance */
   if(0==G__getnumbaseclass(G__get_linked_tagnum(&G__GsimDigiDataDictLN_GsimDigiData))) {
     GsimDigiData *G__Lderived;
     G__Lderived=(GsimDigiData*)0x1000;
     {
       TObject *G__Lpbase=(TObject*)G__Lderived;
       G__inheritance_setup(G__get_linked_tagnum(&G__GsimDigiDataDictLN_GsimDigiData),G__get_linked_tagnum(&G__GsimDigiDataDictLN_TObject),(long)G__Lpbase-(long)G__Lderived,1,1);
     }
   }
}

/*********************************************************
* typedef information setup/
*********************************************************/
extern "C" void G__cpp_setup_typetableGsimDigiDataDict() {

   /* Setting up typedef entry */
   G__search_typename2("Version_t",115,-1,0,-1);
   G__setnewtype(-1,"Class version identifier (short)",0);
   G__search_typename2("vector<ROOT::TSchemaHelper>",117,G__get_linked_tagnum(&G__GsimDigiDataDictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("reverse_iterator<const_iterator>",117,G__get_linked_tagnum(&G__GsimDigiDataDictLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR),0,G__get_linked_tagnum(&G__GsimDigiDataDictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR));
   G__setnewtype(-1,NULL,0);
   G__search_typename2("reverse_iterator<iterator>",117,G__get_linked_tagnum(&G__GsimDigiDataDictLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR),0,G__get_linked_tagnum(&G__GsimDigiDataDictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR));
   G__setnewtype(-1,NULL,0);
   G__search_typename2("vector<TVirtualArray*>",117,G__get_linked_tagnum(&G__GsimDigiDataDictLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("reverse_iterator<const_iterator>",117,G__get_linked_tagnum(&G__GsimDigiDataDictLN_reverse_iteratorlEvectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgRcLcLiteratorgR),0,G__get_linked_tagnum(&G__GsimDigiDataDictLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR));
   G__setnewtype(-1,NULL,0);
   G__search_typename2("reverse_iterator<iterator>",117,G__get_linked_tagnum(&G__GsimDigiDataDictLN_reverse_iteratorlEvectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgRcLcLiteratorgR),0,G__get_linked_tagnum(&G__GsimDigiDataDictLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR));
   G__setnewtype(-1,NULL,0);
}

/*********************************************************
* Data Member information setup/
*********************************************************/

   /* Setting up class,struct,union tag member variable */

   /* GsimDigiData */
static void G__setup_memvarGsimDigiData(void) {
   G__tag_memvar_setup(G__get_linked_tagnum(&G__GsimDigiDataDictLN_GsimDigiData));
   { GsimDigiData *p; p=(GsimDigiData*)0x1000; if (p) { }
   G__memvar_setup((void*)((long)(&p->detID)-(long)(p)),114,0,0,-1,G__defined_typename("UShort_t"),-1,1,"detID=",0,(char*)NULL);
   G__memvar_setup((void*)((long)(&p->modID)-(long)(p)),114,0,0,-1,G__defined_typename("UShort_t"),-1,1,"modID=",0,(char*)NULL);
   G__memvar_setup((void*)((long)(&p->energy)-(long)(p)),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"energy=",0,(char*)NULL);
   G__memvar_setup((void*)((long)(&p->time)-(long)(p)),102,0,0,-1,G__defined_typename("Float_t"),-1,1,"time=",0,(char*)NULL);
   G__memvar_setup((void*)((long)(&p->thisID)-(long)(p)),114,0,0,-1,G__defined_typename("UShort_t"),-1,1,"thisID=",0,(char*)NULL);
   G__memvar_setup((void*)((long)(&p->status)-(long)(p)),114,0,0,-1,G__defined_typename("UShort_t"),-1,1,"status=",0,(char*)NULL);
   G__memvar_setup((void*)((long)(&p->track)-(long)(p)),114,0,0,-1,G__defined_typename("UShort_t"),-1,1,"track=",0,(char*)NULL);
   G__memvar_setup((void*)((long)(&p->mtimeEntry)-(long)(p)),114,0,0,-1,G__defined_typename("UShort_t"),-1,1,"mtimeEntry=",0,(char*)NULL);
   G__memvar_setup((void*)((long)(&p->mtimeSize)-(long)(p)),114,0,0,-1,G__defined_typename("UShort_t"),-1,1,"mtimeSize=",0,(char*)NULL);
   G__memvar_setup((void*)0,85,0,0,G__get_linked_tagnum(&G__GsimDigiDataDictLN_TClass),-1,-2,4,"fgIsA=",0,(char*)NULL);
   }
   G__tag_memvar_reset();
}

extern "C" void G__cpp_setup_memvarGsimDigiDataDict() {
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
static void G__setup_memfuncGsimDigiData(void) {
   /* GsimDigiData */
   G__tag_memfunc_setup(G__get_linked_tagnum(&G__GsimDigiDataDictLN_GsimDigiData));
   G__memfunc_setup("GsimDigiData",1159,G__GsimDigiDataDict_162_0_1, 105, G__get_linked_tagnum(&G__GsimDigiDataDictLN_GsimDigiData), -1, 0, 0, 1, 1, 0, "", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("Clear",487,(G__InterfaceMethod) NULL,121, -1, -1, 0, 1, 1, 1, 0, "C - 'Option_t' 10 '\"\"' opt", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("initializeDataValues",2076,G__GsimDigiDataDict_162_0_3, 121, -1, -1, 0, 0, 1, 1, 0, "", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("dump",438,G__GsimDigiDataDict_162_0_4, 121, -1, -1, 0, 1, 1, 1, 0, "i - - 0 '1' imode", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("Class",502,G__GsimDigiDataDict_162_0_5, 85, G__get_linked_tagnum(&G__GsimDigiDataDictLN_TClass), -1, 0, 0, 3, 1, 0, "", (char*)NULL, (void*) G__func2void( (TClass* (*)())(&GsimDigiData::Class) ), 0);
   G__memfunc_setup("Class_Name",982,G__GsimDigiDataDict_162_0_6, 67, -1, -1, 0, 0, 3, 1, 1, "", (char*)NULL, (void*) G__func2void( (const char* (*)())(&GsimDigiData::Class_Name) ), 0);
   G__memfunc_setup("Class_Version",1339,G__GsimDigiDataDict_162_0_7, 115, -1, G__defined_typename("Version_t"), 0, 0, 3, 1, 0, "", (char*)NULL, (void*) G__func2void( (Version_t (*)())(&GsimDigiData::Class_Version) ), 0);
   G__memfunc_setup("Dictionary",1046,G__GsimDigiDataDict_162_0_8, 121, -1, -1, 0, 0, 3, 1, 0, "", (char*)NULL, (void*) G__func2void( (void (*)())(&GsimDigiData::Dictionary) ), 0);
   G__memfunc_setup("IsA",253,(G__InterfaceMethod) NULL,85, G__get_linked_tagnum(&G__GsimDigiDataDictLN_TClass), -1, 0, 0, 1, 1, 8, "", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("ShowMembers",1132,(G__InterfaceMethod) NULL,121, -1, -1, 0, 1, 1, 1, 0, "u 'TMemberInspector' - 1 - insp", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("Streamer",835,(G__InterfaceMethod) NULL,121, -1, -1, 0, 1, 1, 1, 0, "u 'TBuffer' - 1 - b", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("StreamerNVirtual",1656,G__GsimDigiDataDict_162_0_12, 121, -1, -1, 0, 1, 1, 1, 0, "u 'TBuffer' - 1 - b", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("DeclFileName",1145,G__GsimDigiDataDict_162_0_13, 67, -1, -1, 0, 0, 3, 1, 1, "", (char*)NULL, (void*) G__func2void( (const char* (*)())(&GsimDigiData::DeclFileName) ), 0);
   G__memfunc_setup("ImplFileLine",1178,G__GsimDigiDataDict_162_0_14, 105, -1, -1, 0, 0, 3, 1, 0, "", (char*)NULL, (void*) G__func2void( (int (*)())(&GsimDigiData::ImplFileLine) ), 0);
   G__memfunc_setup("ImplFileName",1171,G__GsimDigiDataDict_162_0_15, 67, -1, -1, 0, 0, 3, 1, 1, "", (char*)NULL, (void*) G__func2void( (const char* (*)())(&GsimDigiData::ImplFileName) ), 0);
   G__memfunc_setup("DeclFileLine",1152,G__GsimDigiDataDict_162_0_16, 105, -1, -1, 0, 0, 3, 1, 0, "", (char*)NULL, (void*) G__func2void( (int (*)())(&GsimDigiData::DeclFileLine) ), 0);
   // automatic copy constructor
   G__memfunc_setup("GsimDigiData", 1159, G__GsimDigiDataDict_162_0_17, (int) ('i'), G__get_linked_tagnum(&G__GsimDigiDataDictLN_GsimDigiData), -1, 0, 1, 1, 1, 0, "u 'GsimDigiData' - 11 - -", (char*) NULL, (void*) NULL, 0);
   // automatic destructor
   G__memfunc_setup("~GsimDigiData", 1285, G__GsimDigiDataDict_162_0_18, (int) ('y'), -1, -1, 0, 0, 1, 1, 0, "", (char*) NULL, (void*) NULL, 1);
   // automatic assignment operator
   G__memfunc_setup("operator=", 937, G__GsimDigiDataDict_162_0_19, (int) ('u'), G__get_linked_tagnum(&G__GsimDigiDataDictLN_GsimDigiData), -1, 1, 1, 1, 1, 0, "u 'GsimDigiData' - 11 - -", (char*) NULL, (void*) NULL, 0);
   G__tag_memfunc_reset();
}


/*********************************************************
* Member function information setup
*********************************************************/
extern "C" void G__cpp_setup_memfuncGsimDigiDataDict() {
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
extern "C" void G__cpp_setup_globalGsimDigiDataDict() {
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

extern "C" void G__cpp_setup_funcGsimDigiDataDict() {
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
G__linked_taginfo G__GsimDigiDataDictLN_TClass = { "TClass" , 99 , -1 };
G__linked_taginfo G__GsimDigiDataDictLN_TBuffer = { "TBuffer" , 99 , -1 };
G__linked_taginfo G__GsimDigiDataDictLN_TMemberInspector = { "TMemberInspector" , 99 , -1 };
G__linked_taginfo G__GsimDigiDataDictLN_TObject = { "TObject" , 99 , -1 };
G__linked_taginfo G__GsimDigiDataDictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR = { "vector<ROOT::TSchemaHelper,allocator<ROOT::TSchemaHelper> >" , 99 , -1 };
G__linked_taginfo G__GsimDigiDataDictLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR = { "reverse_iterator<vector<ROOT::TSchemaHelper,allocator<ROOT::TSchemaHelper> >::iterator>" , 99 , -1 };
G__linked_taginfo G__GsimDigiDataDictLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR = { "vector<TVirtualArray*,allocator<TVirtualArray*> >" , 99 , -1 };
G__linked_taginfo G__GsimDigiDataDictLN_reverse_iteratorlEvectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgRcLcLiteratorgR = { "reverse_iterator<vector<TVirtualArray*,allocator<TVirtualArray*> >::iterator>" , 99 , -1 };
G__linked_taginfo G__GsimDigiDataDictLN_GsimDigiData = { "GsimDigiData" , 99 , -1 };

/* Reset class/struct taginfo */
extern "C" void G__cpp_reset_tagtableGsimDigiDataDict() {
  G__GsimDigiDataDictLN_TClass.tagnum = -1 ;
  G__GsimDigiDataDictLN_TBuffer.tagnum = -1 ;
  G__GsimDigiDataDictLN_TMemberInspector.tagnum = -1 ;
  G__GsimDigiDataDictLN_TObject.tagnum = -1 ;
  G__GsimDigiDataDictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR.tagnum = -1 ;
  G__GsimDigiDataDictLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR.tagnum = -1 ;
  G__GsimDigiDataDictLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR.tagnum = -1 ;
  G__GsimDigiDataDictLN_reverse_iteratorlEvectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgRcLcLiteratorgR.tagnum = -1 ;
  G__GsimDigiDataDictLN_GsimDigiData.tagnum = -1 ;
}


extern "C" void G__cpp_setup_tagtableGsimDigiDataDict() {

   /* Setting up class,struct,union tag entry */
   G__get_linked_tagnum_fwd(&G__GsimDigiDataDictLN_TClass);
   G__get_linked_tagnum_fwd(&G__GsimDigiDataDictLN_TBuffer);
   G__get_linked_tagnum_fwd(&G__GsimDigiDataDictLN_TMemberInspector);
   G__get_linked_tagnum_fwd(&G__GsimDigiDataDictLN_TObject);
   G__get_linked_tagnum_fwd(&G__GsimDigiDataDictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR);
   G__get_linked_tagnum_fwd(&G__GsimDigiDataDictLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR);
   G__get_linked_tagnum_fwd(&G__GsimDigiDataDictLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR);
   G__get_linked_tagnum_fwd(&G__GsimDigiDataDictLN_reverse_iteratorlEvectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgRcLcLiteratorgR);
   G__tagtable_setup(G__get_linked_tagnum_fwd(&G__GsimDigiDataDictLN_GsimDigiData),sizeof(GsimDigiData),-1,292096,(char*)NULL,G__setup_memvarGsimDigiData,G__setup_memfuncGsimDigiData);
}
extern "C" void G__cpp_setupGsimDigiDataDict(void) {
  G__check_setup_version(30051515,"G__cpp_setupGsimDigiDataDict()");
  G__set_cpp_environmentGsimDigiDataDict();
  G__cpp_setup_tagtableGsimDigiDataDict();

  G__cpp_setup_inheritanceGsimDigiDataDict();

  G__cpp_setup_typetableGsimDigiDataDict();

  G__cpp_setup_memvarGsimDigiDataDict();

  G__cpp_setup_memfuncGsimDigiDataDict();
  G__cpp_setup_globalGsimDigiDataDict();
  G__cpp_setup_funcGsimDigiDataDict();

   if(0==G__getsizep2memfunc()) G__get_sizep2memfuncGsimDigiDataDict();
  return;
}
class G__cpp_setup_initGsimDigiDataDict {
  public:
    G__cpp_setup_initGsimDigiDataDict() { G__add_setup_func("GsimDigiDataDict",(G__incsetup)(&G__cpp_setupGsimDigiDataDict)); G__call_setup_funcs(); }
   ~G__cpp_setup_initGsimDigiDataDict() { G__remove_setup_func("GsimDigiDataDict"); }
};
G__cpp_setup_initGsimDigiDataDict G__cpp_setup_initializerGsimDigiDataDict;
