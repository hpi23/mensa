#include "./libSAP/dynstring/dynstring.h"
#include <stdbool.h>
#include <assert.h>
#include "./libSAP/libJson.h"
#include "./libSAP/libTime.h"
#include "./libSAP/libGC.h"
#include "./libSAP/libHttp.h"
#include "./libSAP/libList.h"
#include "./libSAP/libString.h"
#include "./libSAP/libSAP.h"

ListNode* Lade_Speiseangebot0(int64_t, int64_t);
DynString* Haupt1(ListNode*);
DynString* Aktualisiere2(int64_t, int64_t);
DynString* Gericht_Liste_Drucken3(ListNode*);
DynString* Verflache_Ausgabe4(ListNode*);
DynString* bewerbung();
void einschreibung(int64_t);
void studium();
void type_descriptor_setup();
void type_descriptor_teardown();
void global_variable_setup();
void cexit(int);
int64_t lib_main(int, char**);

ListNode* Lade_Speiseangebot0(int64_t Mensa_Ort7, int64_t Tages_Verschiebung8);

DynString* Haupt1(ListNode* Args178);

DynString* Aktualisiere2(int64_t Mensa_Ort226, int64_t Tages_Verschiebung227);

DynString* Gericht_Liste_Drucken3(ListNode* Eingabe277);

DynString* Verflache_Ausgabe4(ListNode* Roh324);

DynString* bewerbung();

void einschreibung(int64_t Matrikelnummer340);

void studium();

void type_descriptor_setup();

void type_descriptor_teardown();

void global_variable_setup();

void cexit(int code);

int64_t lib_main(int argc345, char** argv346);