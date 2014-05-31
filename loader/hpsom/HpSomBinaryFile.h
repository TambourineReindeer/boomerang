/* * Copyright (C) 2000-2001, The University of Queensland
 *
 * See the file "LICENSE.TERMS" for information on usage and
 * redistribution of this file, and for a DISCLAIMER OF ALL
 * WARRANTIES.
 *
 */

/** \file HpSomBinaryFile.h
 * \brief This file contains the definition of the class HpSomBinaryFile.
 */
#ifndef __HPSOMBINARYFILE_H__
#define __HPSOMBINARYFILE_H__

/***************************************************************************//**
 * Dependencies.
 ******************************************************************************/

#include "BinaryFile.h"
#include "../SymTab.h"
#include <set>

struct import_entry {
    int         name;
    short       reserved2;
    Byte        type;
    Byte        reserved1;
};

struct export_entry {
    int         next;
    int         name;
    int         value;
    int         size;       // Also misc_info
    Byte        type;
    char        reserved1;
    short       module_index;
};

struct space_dictionary_record {
    unsigned    name;
    unsigned    flags;
    int         space_number;
    int         subspace_index;
    unsigned    subspace_quantity;
    int         loader_fix_index;
    unsigned    loader_fix_quantity;
    int         init_pointer_index;
    unsigned    init_pointer_quantity;
};

struct subspace_dictionary_record {
    int         space_index;
    unsigned    flags;
    int         file_loc_init_value;
    unsigned    initialization_length;
    unsigned    subspace_start;
    unsigned    subspace_length;
    unsigned    alignment;
    unsigned    name;
    int         fixup_request_index;
    int         fixup_request_quantity;
};

struct plt_record {
    ADDRESS     value;                      // Address in the library
    ADDRESS     r19value;                   // r19 value needed
};

struct symElem {
    const char* name;                       // Simple symbol table entry
    ADDRESS     value;
};

class HpSomBinaryFile : public QObject,
        public BinaryData,
        public LoaderInterface,
        public LoaderCommon {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID LoaderInterface_iid)
    Q_INTERFACES(LoaderInterface)
    Q_INTERFACES(BinaryData)
    Q_INTERFACES(SectionInterface)
public:
    HpSomBinaryFile();          // Constructor
    virtual             ~HpSomBinaryFile();
    void        UnLoad() override;                   // Unload the image
    bool        Open(const char* sName) override;    // Open the file for r/w; pv
    void        Close() override;                    // Close file opened with Open()
    bool        PostLoad(void* handle) override;     // For archive files only
    virtual LOAD_FMT    GetFormat() const;       // Get format i.e. LOADFMT_PALM
    virtual MACHINE     GetMachine() const;       // Get format i.e. MACHINE_HPRISC
    QString getFilename() const override { return m_pFileName; }

    virtual bool        isLibrary() const;
    virtual QStringList getDependencyList();
    virtual ADDRESS     getImageBase();
    virtual size_t      getImageSize();

    // Get a symbol given an address
    virtual const char* SymbolByAddress(ADDRESS dwAddr);
    // Lookup the name, return the address
    virtual ADDRESS     GetAddressByName(const char* pName, bool bNoTypeOK = false);
    // Return true if the address matches the convention for A-line system calls
    bool        IsDynamicLinkedProc(ADDRESS uNative);

    // Specific to BinaryFile objects that implement a "global pointer"
    // Gets a pair of unsigned integers representing the address of %agp (first)
    // and the value for GLOBALOFFSET (unused for pa-risc)
    virtual std::pair<ADDRESS,unsigned> GetGlobalPointerInfo();

    // Get a map from ADDRESS to const char*. This map contains the native
    // addresses and symbolic names of global data items (if any) which are
    // shared with dynamically linked libraries. Example: __iob (basis for
    // stdout).The ADDRESS is the native address of a pointer to the real dynamic data object.
    virtual std::map<ADDRESS, const char*>* GetDynamicGlobalMap();

    //
    //  --  --  --  --  --  --  --  --  --  --  --
    //
    // Internal information
    // Dump headers, etc
    //virtual bool    DisplayDetails(const char* fileName, FILE* f = stdout);


    // Analysis functions
    virtual std::list<SectionInfo*>& GetEntryPoints(const char* pEntry = "main");
    virtual ADDRESS        GetMainEntryPoint();
    virtual ADDRESS        GetEntryPoint();

    //        bool        IsDynamicLinkedProc(ADDRESS wNative);
    //        ADDRESS     NativeToHostAddress(ADDRESS uNative);
    char readNative1(ADDRESS nat);
    int readNative2(ADDRESS nat);
    int readNative4(ADDRESS nat);
    float readNativeFloat4(ADDRESS nat);
    double readNativeFloat8(ADDRESS nat);
    QWord readNative8(ADDRESS nat);
protected:
    bool RealLoad(const QString &sName) override; // Load the file; pure virtual


private:
    // Private method to get the start and length of a given subspace
    std::pair<ADDRESS, int> getSubspaceInfo(const char* ssname);

    unsigned char* m_pImage;                    // Points to loaded image
    SymTab        symbols;                    // Symbol table object
    //        ADDRESS        mainExport;                    // Export entry for "main"
    std::set<ADDRESS> imports;                // Set of imported proc addr's
    QString m_pFileName;

    // LoaderInterface interface
public:
    tMapAddrToString &getSymbols();
};

#endif      // #ifndef __HPSOMBINARYFILE_H__