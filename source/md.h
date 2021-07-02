//~ Metadesk Library
// LICENSE AT END OF FILE (MIT).

// TODO List
//
// [x] unify string literal token kinds
// [x] simplify string literal flags (triple as a single flag)
// [x] lexer detects broken comments
// [x] lexer detects broken strings
// [x] tests for legal tag syntaxes
// [x] tests that ensure we don't accept labels when expecting symbols e.g. foo ":" b; foo: "(" )
// [x] pass all tests
// [ ] simplify error sorting and catastrophic error handling
// [ ] integer -> string helpers
// [x] {rjf} remove symbol digraphs (maybe a test for this or something) and remove from comments
// [x] stb_snprintf included and modified for %S ~ MD_String8
// [ ] naming pass
// [ ] {rjf} get the branches/labels setup on Git for beta 0.1 and dev
// [ ] {rjf} announcement

// NOTE(allen): "Plugin" functionality
//
// MD_b32     MD_IMPL_FileIterIncrement(MD_FileIter*, MD_String8, MD_FileInfo*) - optional
// void*      MD_IMPL_Alloc(MD_u64)                                             - required
//

#ifndef MD_H
#define MD_H

// NOTE(rjf): Compiler cracking from the 4th dimension

#if defined(_MSC_VER)

# define MD_COMPILER_CL 1

# if defined(_WIN32)
#  define MD_OS_WINDOWS 1
# else
#  error This compiler/platform combo is not supported yet
# endif

# if defined(_M_AMD64)
#  define MD_ARCH_X64 1
# elif defined(_M_IX86)
#  define MD_ARCH_X86 1
# elif defined(_M_ARM64)
#  define MD_ARCH_ARM64 1
# elif defined(_M_ARM)
#  define MD_ARCH_ARM32 1
# else
#  error architecture not supported yet
# endif

# if _MSC_VER >= 1920
#  define MD_COMPILER_CL_YEAR 2019
# elif _MSC_VER >= 1910
#  define MD_COMPILER_CL_YEAR 2017
# elif _MSC_VER >= 1900
#  define MD_COMPILER_CL_YEAR 2015
# elif _MSC_VER >= 1800
#  define MD_COMPILER_CL_YEAR 2013
# elif _MSC_VER >= 1700
#  define MD_COMPILER_CL_YEAR 2012
# elif _MSC_VER >= 1600
#  define MD_COMPILER_CL_YEAR 2010
# elif _MSC_VER >= 1500
#  define MD_COMPILER_CL_YEAR 2008
# elif _MSC_VER >= 1400
#  define MD_COMPILER_CL_YEAR 2005
# else
#  define MD_COMPILER_CL_YEAR 0
# endif

#elif defined(__clang__)

# define MD_COMPILER_CLANG 1

# if defined(__APPLE__) && defined(__MACH__)
#  define MD_OS_MAC 1
# elif defined(__gnu_linux__)
#  define MD_OS_LINUX 1
# else
#  error This compiler/platform combo is not supported yet
# endif

# if defined(__amd64__) || defined(__amd64) || defined(__x86_64__) || defined(__x86_64)
#  define MD_ARCH_X64 1
# elif defined(i386) || defined(__i386) || defined(__i386__)
#  define MD_ARCH_X86 1
# elif defined(__aarch64__)
#  define MD_ARCH_ARM64 1
# elif defined(__arm__)
#  define MD_ARCH_ARM32 1
# else
#  error architecture not supported yet
# endif

#elif defined(__GNUC__) || defined(__GNUG__)

# define MD_COMPILER_GCC 1

# if defined(__gnu_linux__)
#  define MD_OS_LINUX 1
# else
#  error This compiler/platform combo is not supported yet
# endif

# if defined(__amd64__) || defined(__amd64) || defined(__x86_64__) || defined(__x86_64)
#  define MD_ARCH_X64 1
# elif defined(i386) || defined(__i386) || defined(__i386__)
#  define MD_ARCH_X86 1
# elif defined(__aarch64__)
#  define MD_ARCH_ARM64 1
# elif defined(__arm__)
#  define MD_ARCH_ARM32 1
# else
#  error architecture not supported yet
# endif

#else
# error This compiler is not supported yet
#endif

#if defined(MD_ARCH_X64)
# define MD_ARCH_64BIT 1
#elif defined(MD_ARCH_X86)
# define MD_ARCH_32BIT 1
#endif

#if defined(__cplusplus)
# define MD_LANG_CPP 1
#else
# define MD_LANG_C 1
#endif

// zeroify

#if !defined(MD_ARCH_32BIT)
# define MD_ARCH_32BIT 0
#endif
#if !defined(MD_ARCH_64BIT)
# define MD_ARCH_64BIT 0
#endif
#if !defined(MD_ARCH_X64)
# define MD_ARCH_X64 0
#endif
#if !defined(MD_ARCH_X86)
# define MD_ARCH_X86 0
#endif
#if !defined(MD_ARCH_ARM64)
# define MD_ARCH_ARM64 0
#endif
#if !defined(MD_ARCH_ARM32)
# define MD_ARCH_ARM32 0
#endif
#if !defined(MD_COMPILER_CL)
# define MD_COMPILER_CL 0
#endif
#if !defined(MD_COMPILER_GCC)
# define MD_COMPILER_GCC 0
#endif
#if !defined(MD_COMPILER_CLANG)
# define MD_COMPILER_CLANG 0
#endif
#if !defined(MD_OS_WINDOWS)
# define MD_OS_WINDOWS 0
#endif
#if !defined(MD_OS_LINUX)
# define MD_OS_LINUX 0
#endif
#if !defined(MD_OS_MAC)
# define MD_OS_MAC 0
#endif
#if !defined(MD_LANG_C)
# define MD_LANG_C 0
#endif
#if !defined(MD_LANG_CPP)
# define MD_LANG_CPP 0
#endif

#if MD_LANG_CPP
# define MD_ZERO_STRUCT {}
#else
# define MD_ZERO_STRUCT {0}
#endif

#if MD_LANG_C
# define MD_C_LINKAGE_BEGIN
# define MD_C_LINKAGE_END
#else
# define MD_C_LINKAGE_BEGIN extern "C"{
# define MD_C_LINKAGE_END }
#endif

//~ Common defines

#define MD_FUNCTION
#define MD_GLOBAL static

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#define STB_SPRINTF_DECORATE(name) md_stbsp_##name
#include "md_stb_sprintf.h"

typedef int8_t   MD_i8;
typedef int16_t  MD_i16;
typedef int32_t  MD_i32;
typedef int64_t  MD_i64;
typedef uint8_t  MD_u8;
typedef uint16_t MD_u16;
typedef uint32_t MD_u32;
typedef uint64_t MD_u64;
typedef int8_t   MD_b8;
typedef int16_t  MD_b16;
typedef int32_t  MD_b32;
typedef int64_t  MD_b64;
typedef float    MD_f32;
typedef double   MD_f64;

//~ Basic Unicode string types.

typedef struct MD_String8 MD_String8;
struct MD_String8
{
    MD_u8 *str;
    MD_u64 size;
};

typedef struct MD_String16 MD_String16;
struct MD_String16
{
    MD_u16 *str;
    MD_u64 size;
};

typedef struct MD_String32 MD_String32;
struct MD_String32
{
    MD_u32 *str;
    MD_u64 size;
};

typedef struct MD_String8Node MD_String8Node;
struct MD_String8Node
{
    MD_String8Node *next;
    MD_String8 string;
};

typedef struct MD_String8List MD_String8List;
struct MD_String8List
{
    MD_u64 node_count;
    MD_u64 total_size;
    MD_String8Node *first;
    MD_String8Node *last;
};

// NOTE(rjf): @maintenance These three enums must not overlap, and must share a flag space.
typedef MD_u32 MD_MatchFlags;
typedef MD_u32 MD_StringMatchFlags;
typedef MD_u32 MD_NodeMatchFlags;
enum
{
    MD_MatchFlag_FindLast = (1<<0),
};
enum
{
    MD_StringMatchFlag_CaseInsensitive  = (1<<4),
    MD_StringMatchFlag_RightSideSloppy  = (1<<5),
    MD_StringMatchFlag_SlashInsensitive = (1<<6),
};
enum
{
    MD_NodeMatchFlag_Tags             = (1<<16),
    MD_NodeMatchFlag_TagArguments     = (1<<17),
};

typedef struct MD_DecodedCodepoint MD_DecodedCodepoint;
struct MD_DecodedCodepoint
{
    MD_u32 codepoint;
    MD_u32 advance;
};

typedef enum MD_IdentifierStyle
{
    MD_IdentifierStyle_UpperCamelCase,
    MD_IdentifierStyle_LowerCamelCase,
    MD_IdentifierStyle_UpperCase,
    MD_IdentifierStyle_LowerCase,
}
MD_IdentifierStyle;

//~ Node types that are used to build all ASTs.

typedef enum MD_NodeKind
{
    // NOTE(rjf): @maintenance Must be kept in sync with MD_StringFromNodeKind.
    
    MD_NodeKind_Nil,
    
    // NOTE(rjf): Generated by parser
    MD_NodeKind_File,
    MD_NodeKind_ErrorMarker,
    
    // NOTE(rjf): Parsed from user Metadesk code
    MD_NodeKind_Main,
    MD_NodeKind_Tag,
    
    // NOTE(rjf): User-created data structures
    MD_NodeKind_List,
    MD_NodeKind_Reference,
    
    MD_NodeKind_COUNT,
}
MD_NodeKind;

typedef MD_u64 MD_NodeFlags;
#define MD_NodeFlag_AfterFromBefore(f) ((f) << 1)
enum
{
    // NOTE(rjf): @maintenance Must be kept in sync with MD_StringListFromNodeFlags.
    
    // NOTE(rjf): @maintenance Because of MD_NodeFlag_AfterFromBefore, it is
    // *required* that every single pair of "Before*" or "After*" flags be in
    // the correct order which is that the Before* flag comes first, and the
    // After* flag comes immediately after (After* being the more significant
    // bit).
    
    MD_NodeFlag_HasParenLeft               = (1<<0),
    MD_NodeFlag_HasParenRight              = (1<<1),
    MD_NodeFlag_HasBracketLeft             = (1<<2),
    MD_NodeFlag_HasBracketRight            = (1<<3),
    MD_NodeFlag_HasBraceLeft               = (1<<4),
    MD_NodeFlag_HasBraceRight              = (1<<5),
    
    MD_NodeFlag_IsBeforeSemicolon          = (1<<6),
    MD_NodeFlag_IsAfterSemicolon           = (1<<7),
    
    MD_NodeFlag_IsBeforeComma              = (1<<8),
    MD_NodeFlag_IsAfterComma               = (1<<9),
    
    MD_NodeFlag_StringSingleQuote       = (1<<10),
    MD_NodeFlag_StringDoubleQuote       = (1<<11),
    MD_NodeFlag_StringTick              = (1<<12),
    MD_NodeFlag_StringTriplet           = (1<<13),
    
    MD_NodeFlag_Numeric                 = (1<<14),
    MD_NodeFlag_Identifier              = (1<<15),
    MD_NodeFlag_StringLiteral           = (1<<16),
};

typedef struct MD_Node MD_Node;
struct MD_Node
{
    // Tree relationship data.
    MD_Node *next;
    MD_Node *prev;
    MD_Node *parent;
    MD_Node *first_child;
    MD_Node *last_child;
    
    // Tag list.
    MD_Node *first_tag;
    MD_Node *last_tag;
    
    // Node info.
    MD_NodeKind kind;
    MD_NodeFlags flags;
    MD_String8 string;
    MD_String8 raw_string;
    MD_u64 string_hash;
    
    // Comments.
    MD_String8 prev_comment;
    MD_String8 next_comment;
    
    // Source code location information.
    MD_u64 offset;
    
    // Reference.
    MD_Node *ref_target;
};

//~ Code Location Info.

typedef struct MD_CodeLoc MD_CodeLoc;
struct MD_CodeLoc
{
    MD_String8 filename;
    MD_u32 line;
    MD_u32 column;
};

//~ String-To-Ptr and Ptr-To-Ptr tables

typedef struct MD_MapKey MD_MapKey;
struct MD_MapKey
{
    MD_u64 hash;
    MD_u64 size;
    void *ptr;
};

typedef struct MD_MapSlot MD_MapSlot;
struct MD_MapSlot
{
    MD_MapSlot *next;
    MD_MapKey key;
    void *val;
};

typedef struct MD_MapBucket MD_MapBucket;
struct MD_MapBucket
{
    MD_MapSlot *first;
    MD_MapSlot *last;
};

typedef struct MD_Map MD_Map;
struct MD_Map
{
    MD_MapBucket *buckets;
    MD_u64 bucket_count;
};

//~ Tokens

typedef MD_u32 MD_TokenKind;
enum
{
    MD_TokenKind_Identifier          = (1<<0),
    MD_TokenKind_NumericLiteral      = (1<<1),
    MD_TokenKind_StringLiteral       = (1<<2),
    MD_TokenKind_Symbol              = (1<<3),
    MD_TokenKind_Reserved            = (1<<4),
    MD_TokenKind_Comment             = (1<<5),
    MD_TokenKind_Whitespace          = (1<<6),
    MD_TokenKind_Newline             = (1<<7),
    MD_TokenKind_BrokenComment       = (1<<8),
    MD_TokenKind_BrokenStringLiteral = (1<<9),
    MD_TokenKind_BadCharacter        = (1<<10),
};

typedef MD_u32 MD_TokenGroups;
enum
{
    MD_TokenGroup_Comment = MD_TokenKind_Comment,
    MD_TokenGroup_Whitespace = (MD_TokenKind_Whitespace|
                                MD_TokenKind_Newline),
    MD_TokenGroup_Irregular = (MD_TokenGroup_Comment|
                               MD_TokenGroup_Whitespace),
    MD_TokenGroup_Regular = ~MD_TokenGroup_Irregular,
    MD_TokenGroup_Label   = (MD_TokenKind_Identifier|
                             MD_TokenKind_NumericLiteral|
                             MD_TokenKind_StringLiteral|
                             MD_TokenKind_Symbol),
    MD_TokenGroup_Error   = (MD_TokenKind_BrokenComment|
                             MD_TokenKind_BrokenStringLiteral|
                             MD_TokenKind_BadCharacter),
};

typedef struct MD_Token MD_Token;
struct MD_Token
{
    MD_TokenKind kind;
    MD_NodeFlags node_flags;
    MD_String8 string;
    MD_String8 raw_string;
};

//~ Parsing State

typedef enum MD_MessageKind
{
    // NOTE(rjf): @maintenance This enum needs to be sorted in order of
    // severity.
    MD_MessageKind_Null,
    MD_MessageKind_Note,
    MD_MessageKind_Warning,
    MD_MessageKind_Error,
    MD_MessageKind_CatastrophicError,
}
MD_MessageKind;

typedef struct MD_Message MD_Message;
struct MD_Message
{
    MD_Message *next;
    MD_Node *node;
    MD_MessageKind kind;
    MD_String8 string;
};

typedef struct MD_MessageList MD_MessageList;
struct MD_MessageList
{
    MD_MessageKind max_message_kind;
    MD_u64 node_count;
    MD_Message *first;
    MD_Message *last;
};

typedef enum MD_ParseSetRule
{
    MD_ParseSetRule_EndOnDelimiter,
    MD_ParseSetRule_Global,
}
MD_ParseSetRule;

typedef struct MD_ParseResult MD_ParseResult;
struct MD_ParseResult
{
    MD_Node *node;
    // TODO(rjf): Remove once we're not using it for ParseTagList
    MD_Node *last_node;
    MD_u64 string_advance;
    MD_MessageList errors;
};

//~ Command line parsing helper types.

typedef struct MD_CmdLineOption MD_CmdLineOption;
struct MD_CmdLineOption
{
    MD_CmdLineOption *next;
    MD_String8 name;
    MD_String8List values;
};

typedef struct MD_CmdLine MD_CmdLine;
struct MD_CmdLine
{
    MD_String8List inputs;
    MD_CmdLineOption *first_option;
    MD_CmdLineOption *last_option;
};

//~ File system access types.

typedef MD_u32 MD_FileFlags;
enum
{
    MD_FileFlag_Directory = (1<<0),
};

typedef struct MD_FileInfo MD_FileInfo;
struct MD_FileInfo
{
    MD_FileFlags flags;
    MD_String8 filename;
    MD_u64 file_size;
};

typedef struct MD_FileIter MD_FileIter;
struct MD_FileIter
{
    // This is opaque state to store OS-specific file-system iteration data.
    MD_u64 state[2];
};

//~ Basic Utilities

#define MD_Assert(c) if (!(c)) { *(volatile MD_u64 *)0 = 0; }
#define MD_StaticAssert(c,label) MD_u8 MD_static_assert_##label[(c)?(1):(-1)]
#define MD_ArrayCount(a) (sizeof(a) / sizeof((a)[0]))

//~ Linked List Macros.

// terminator modes
#define MD_CheckNull(p) ((p)==0)
#define MD_SetNull(p) ((p)=0)
#define MD_CheckNil(p) (MD_NodeIsNil(p))
#define MD_SetNil(p) ((p)=MD_NilNode())

// implementations
#define MD_QueuePush_NZ(f,l,n,next,zchk,zset) (zchk(f)?\
(f)=(l)=(n):\
((l)->next=(n),(l)=(n),zset((n)->next)))
#define MD_QueuePop_NZ(f,l,next,zset) ((f)==(l)?\
(zset(f),zset(l)):\
(f)=(f)->next)
#define MD_StackPush_N(f,n,next) ((n)->next=(f),(f)=(n))
#define MD_StackPop_NZ(f,next,zchk) (zchk(f)?0:(f)=(f)->next)

#define MD_DblPushBack_NPZ(f,l,n,next,prev,zchk,zset) \
(zchk(f)?\
((f)=(l)=(n),zset((n)->next),zset((n)->prev)):\
((n)->prev=(l),(l)->next=(n),(l)=(n),zset((n)->next)))
#define MD_DblRemove_NPZ(f,l,n,next,prev,zset) (((f)==(n)?\
((f)=(f)->next,zset((f)->prev)):\
(l)==(n)?\
((l)=(l)->prev,zset((l)->next)):\
((n)->next->prev=(n)->prev,\
(n)->prev->next=(n)->next)))

// compositions
#define MD_QueuePush(f,l,n) MD_QueuePush_NZ(f,l,n,next,MD_CheckNull,MD_SetNull)
#define MD_QueuePop(f,l)    MD_QueuePop_NZ(f,l,next,MD_SetNull)
#define MD_StackPush(f,n)   MD_StackPush_N(f,n,next)
#define MD_StackPop(f)      MD_StackPop_NZ(f,next,MD_CheckNull)
#define MD_DblPushBack(f,l,n)  MD_DblPushBack_NPZ(f,l,n,next,prev,MD_CheckNull,MD_SetNull)
#define MD_DblPushFront(f,l,n) MD_DblPushBack_NPZ(l,f,n,prev,next,MD_CheckNull,MD_SetNull)
#define MD_DblRemove(f,l,n)    MD_DblRemove_NPZ(f,l,n,next,prev,MD_SetNull)

#define MD_NodeDblPushBack(f,l,n)  MD_DblPushBack_NPZ(f,l,n,next,prev,MD_CheckNil,MD_SetNil)
#define MD_NodeDblPushFront(f,l,n) MD_DblPushBack_NPZ(l,f,n,prev,next,MD_CheckNil,MD_SetNil)
#define MD_NodeDblRemove(f,l,n)    MD_DblRemove_NPZ(f,l,n,next,prev,MD_SetNil)


//~ Memory Operations

MD_FUNCTION void MD_MemoryZero(void *memory, MD_u64 size);
MD_FUNCTION void MD_MemoryCopy(void *dst, void *src, MD_u64 size);

MD_FUNCTION void* MD_AllocZero(MD_u64 size);
#define MD_PushArray(T,c) (T*)MD_AllocZero(sizeof(T)*(c))
// NOTE(rjf): Right now, both calls just automatically zero their memory,
// but I'm explicitly splitting this out to ensure that we don't accidentally
// assume that we have zeroed memory incorrectly in the future (when our
// allocation approach changes).
#define MD_PushArrayZero(T,c) (T*)MD_AllocZero(sizeof(T)*(c))

//~ Characters

MD_FUNCTION MD_b32 MD_CharIsAlpha(MD_u8 c);
MD_FUNCTION MD_b32 MD_CharIsAlphaUpper(MD_u8 c);
MD_FUNCTION MD_b32 MD_CharIsAlphaLower(MD_u8 c);
MD_FUNCTION MD_b32 MD_CharIsDigit(MD_u8 c);
MD_FUNCTION MD_b32 MD_CharIsUnreservedSymbol(MD_u8 c);
MD_FUNCTION MD_b32 MD_CharIsReservedSymbol(MD_u8 c);
MD_FUNCTION MD_b32 MD_CharIsSpace(MD_u8 c);
MD_FUNCTION MD_u8  MD_CharToUpper(MD_u8 c);
MD_FUNCTION MD_u8  MD_CharToLower(MD_u8 c);
MD_FUNCTION MD_u8  MD_CharToForwardSlash(MD_u8 c);

//~ Strings

MD_FUNCTION MD_u64         MD_CalculateCStringLength(char *cstr);

MD_FUNCTION MD_String8     MD_S8(MD_u8 *str, MD_u64 size);
#define MD_S8CString(s)    MD_S8((MD_u8 *)(s), MD_CalculateCStringLength(s))

#if MD_LANG_C
# define MD_S8Lit(s)        (MD_String8){(MD_u8 *)(s), sizeof(s)-1}
#elif MD_LANG_CPP
# define MD_S8Lit(s)        MD_S8((MD_u8*)(s), sizeof(s) - 1)
#endif
#define MD_S8LitComp(s)     {(MD_u8 *)(s), sizeof(s)-1}

#if MD_LANG_CPP
// TODO(rjf): @allen this is only supported in C++11 I think, we need a check
// for that in the context cracking
static inline MD_String8
operator "" _md(const char *s, size_t size)
{
    MD_String8 str = MD_S8((MD_u8 *)s, (MD_u64)size);
    return str;
}
#endif

MD_FUNCTION MD_String8     MD_S8Range(MD_u8 *first, MD_u8 *opl);

MD_FUNCTION MD_String8     MD_S8Substring(MD_String8 str, MD_u64 min, MD_u64 max);
MD_FUNCTION MD_String8     MD_S8Skip(MD_String8 str, MD_u64 min);
MD_FUNCTION MD_String8     MD_S8Chop(MD_String8 str, MD_u64 nmax);
MD_FUNCTION MD_String8     MD_S8Prefix(MD_String8 str, MD_u64 size);
MD_FUNCTION MD_String8     MD_S8Suffix(MD_String8 str, MD_u64 size);

MD_FUNCTION MD_b32         MD_S8Match(MD_String8 a, MD_String8 b, MD_MatchFlags flags);
MD_FUNCTION MD_u64         MD_S8FindSubstring(MD_String8 str, MD_String8 substring,
                                              MD_u64 start_pos, MD_MatchFlags flags);

MD_FUNCTION MD_String8     MD_S8Copy(MD_String8 string);
MD_FUNCTION MD_String8     MD_S8FmtV(char *fmt, va_list args);

MD_FUNCTION MD_String8     MD_S8Fmt(char *fmt, ...);

#define MD_S8VArg(s) (int)(s).size, (s).str

MD_FUNCTION void           MD_S8ListPush(MD_String8List *list, MD_String8 string);
MD_FUNCTION void           MD_S8ListConcat(MD_String8List *list, MD_String8List *to_push);
MD_FUNCTION MD_String8List MD_S8Split(MD_String8 string, int split_count, MD_String8 *splits);
MD_FUNCTION MD_String8     MD_S8ListJoin(MD_String8List list, MD_String8 separator);

MD_FUNCTION MD_String8     MD_S8Stylize(MD_String8 string, MD_IdentifierStyle word_style, MD_String8 separator);

//~ Unicode Conversions

MD_FUNCTION MD_DecodedCodepoint MD_DecodeCodepointFromUtf8(MD_u8 *str, MD_u64 max);
MD_FUNCTION MD_DecodedCodepoint MD_DecodeCodepointFromUtf16(MD_u16 *str, MD_u64 max);
MD_FUNCTION MD_u32         MD_Utf8FromCodepoint(MD_u8 *out, MD_u32 codepoint);
MD_FUNCTION MD_u32         MD_Utf16FromCodepoint(MD_u16 *out, MD_u32 codepoint);
MD_FUNCTION MD_String8     MD_S8FromS16(MD_String16 str);
MD_FUNCTION MD_String16    MD_S16FromS8(MD_String8 str);
MD_FUNCTION MD_String8     MD_S8FromS32(MD_String32 str);
MD_FUNCTION MD_String32    MD_S32FromS8(MD_String8 str);

//~ File Name Strings

// This is intended for removing extensions.
MD_FUNCTION MD_String8 MD_PathChopLastPeriod(MD_String8 string);

// This is intended for removing everything but the filename.
MD_FUNCTION MD_String8 MD_PathSkipLastSlash(MD_String8 string);

// This is intended for getting an extension from a filename.
MD_FUNCTION MD_String8 MD_PathSkipLastPeriod(MD_String8 string);

// This is intended for getting the folder string from a full path.
MD_FUNCTION MD_String8 MD_PathChopLastSlash(MD_String8 string);

//~ Numeric Strings

MD_FUNCTION MD_u64         MD_U64FromString(MD_String8 string, MD_u32 radix);
MD_FUNCTION MD_i64         MD_CStyleIntFromString(MD_String8 string);
MD_FUNCTION MD_f64         MD_F64FromString(MD_String8 string);

//~ Enum/Flag Strings

MD_FUNCTION MD_String8     MD_StringFromNodeKind(MD_NodeKind kind);
MD_FUNCTION MD_String8List MD_StringListFromNodeFlags(MD_NodeFlags flags);

//~ Map Table Data Structure

MD_FUNCTION MD_u64 MD_HashStr(MD_String8 string);
MD_FUNCTION MD_u64 MD_HashPtr(void *p);

MD_FUNCTION MD_Map      MD_MapMakeBucketCount(MD_u64 bucket_count);
MD_FUNCTION MD_Map      MD_MapMake(void);
MD_FUNCTION MD_MapKey   MD_MapKeyStr(MD_String8 string);
MD_FUNCTION MD_MapKey   MD_MapKeyPtr(void *ptr);
MD_FUNCTION MD_MapSlot* MD_MapLookup(MD_Map *map, MD_MapKey key);
MD_FUNCTION MD_MapSlot* MD_MapScan(MD_MapSlot *first_slot, MD_MapKey key);
MD_FUNCTION MD_MapSlot* MD_MapInsert(MD_Map *map, MD_MapKey key, void *val);
MD_FUNCTION MD_MapSlot* MD_MapOverwrite(MD_Map *map, MD_MapKey key, void *val);

//~ Parsing

MD_FUNCTION MD_b32         MD_TokenGroupContainsKind(MD_TokenGroups groups, MD_TokenKind kind);
MD_FUNCTION MD_Token       MD_TokenFromString(MD_String8 string);
MD_FUNCTION MD_u64         MD_LexAdvanceFromSkips(MD_String8 string, MD_TokenKind skip_kinds);
MD_FUNCTION MD_Message *   MD_MakeNodeError(MD_Node *node, MD_MessageKind kind, MD_String8 str);
MD_FUNCTION MD_Message *   MD_MakeTokenError(MD_String8 parse_contents, MD_Token token, MD_MessageKind kind, MD_String8 str);
MD_FUNCTION void           MD_MessageListPush(MD_MessageList *list, MD_Message *message);
MD_FUNCTION void           MD_MessageListConcat(MD_MessageList *list, MD_MessageList *to_push);
MD_FUNCTION MD_ParseResult MD_ParseResultZero(void);
MD_FUNCTION MD_ParseResult MD_ParseOneNode(MD_String8 string, MD_u64 offset);
MD_FUNCTION MD_ParseResult MD_ParseWholeString(MD_String8 filename, MD_String8 contents);

MD_FUNCTION MD_ParseResult MD_ParseWholeFile(MD_String8 filename);

//~ Location Conversion

MD_FUNCTION MD_CodeLoc MD_CodeLocFromFileOffset(MD_String8 filename, MD_u8 *base, MD_u64 offset);
MD_FUNCTION MD_CodeLoc MD_CodeLocFromNode(MD_Node *node);

//~ Tree/List Building

MD_FUNCTION MD_b32   MD_NodeIsNil(MD_Node *node);
MD_FUNCTION MD_Node *MD_NilNode(void);
MD_FUNCTION MD_Node *MD_MakeNode(MD_NodeKind kind, MD_String8 string, MD_String8 raw_string, MD_u64 offset);
MD_FUNCTION void     MD_PushChild(MD_Node *parent, MD_Node *new_child);
MD_FUNCTION void     MD_PushTag(MD_Node *node, MD_Node *tag);

MD_FUNCTION MD_Node *MD_MakeList(void);
MD_FUNCTION MD_Node *MD_PushNewReference(MD_Node *list, MD_Node *target);

//~ Introspection Helpers

// These calls are for getting info from nodes, and introspecting
// on trees that are returned to you by the parser.

MD_FUNCTION MD_Node *  MD_NodeFromString(MD_Node *first, MD_Node *one_past_last, MD_String8 string, MD_MatchFlags flags);
MD_FUNCTION MD_Node *  MD_NodeFromIndex(MD_Node *first, MD_Node *one_past_last, int n);
MD_FUNCTION MD_Node *  MD_NodeFromFlags(MD_Node *first, MD_Node *one_past_last, MD_NodeFlags flags);
MD_FUNCTION int        MD_IndexFromNode(MD_Node *node);
MD_FUNCTION MD_Node *  MD_RootFromNode(MD_Node *node);
MD_FUNCTION MD_Node *  MD_ChildFromString(MD_Node *node, MD_String8 child_string, MD_MatchFlags flags);
MD_FUNCTION MD_Node *  MD_TagFromString(MD_Node *node, MD_String8 tag_string, MD_MatchFlags flags);
MD_FUNCTION MD_Node *  MD_ChildFromIndex(MD_Node *node, int n);
MD_FUNCTION MD_Node *  MD_TagFromIndex(MD_Node *node, int n);
MD_FUNCTION MD_Node *  MD_TagArgFromIndex(MD_Node *node, MD_String8 tag_string, MD_MatchFlags flags, int n);
MD_FUNCTION MD_Node *  MD_TagArgFromString(MD_Node *node, MD_String8 tag_string, MD_MatchFlags tag_str_flags, MD_String8 arg_string, MD_MatchFlags arg_str_flags);
MD_FUNCTION MD_b32     MD_NodeHasTag(MD_Node *node, MD_String8 tag_string, MD_MatchFlags flags);
MD_FUNCTION MD_i64     MD_ChildCountFromNode(MD_Node *node);
MD_FUNCTION MD_i64     MD_TagCountFromNode(MD_Node *node);
MD_FUNCTION MD_Node *  MD_NodeFromReference(MD_Node *node);

// NOTE(rjf): For-Loop Helpers
#define MD_EachNode(it, first) MD_Node *it = (first); !MD_NodeIsNil(it); it = it->next
#define MD_EachNodeRef(it, first) MD_Node *it##_r = (first), *it = MD_NodeFromReference(it##_r); \
!MD_NodeIsNil(it##_r); \
it##_r = it##_r->next, it = MD_NodeFromReference(it##_r)

//~ Error/Warning Helpers

MD_FUNCTION void MD_PrintMessage(FILE *out, MD_CodeLoc loc, MD_MessageKind kind, MD_String8 str);
MD_FUNCTION void MD_PrintMessageFmt(FILE *out, MD_CodeLoc loc, MD_MessageKind kind, char *fmt, ...);
MD_FUNCTION void MD_PrintNodeMessage(FILE *out, MD_Node *node, MD_MessageKind kind, MD_String8 str);
MD_FUNCTION void MD_PrintNodeMessageFmt(FILE *out, MD_Node *node, MD_MessageKind kind, char *fmt, ...);

//~ Tree Comparison/Verification

MD_FUNCTION MD_b32 MD_NodeMatch(MD_Node *a, MD_Node *b, MD_MatchFlags flags);
MD_FUNCTION MD_b32 MD_NodeDeepMatch(MD_Node *a, MD_Node *b, MD_MatchFlags flags);

//~ Generation

MD_FUNCTION void MD_DebugOutputTree(FILE *file, MD_Node *node, int indent_spaces);

//~ Command Line Argument Helper

MD_FUNCTION MD_String8List MD_StringListFromArgCV(int argument_count, char **arguments);
MD_FUNCTION MD_CmdLine MD_MakeCmdLineFromOptions(MD_String8List options);
MD_FUNCTION MD_String8List MD_CmdLineValuesFromString(MD_CmdLine cmdln, MD_String8 name);
MD_FUNCTION MD_b32 MD_CmdLineB32FromString(MD_CmdLine cmdln, MD_String8 name);
MD_FUNCTION MD_i64 MD_CmdLineI64FromString(MD_CmdLine cmdln, MD_String8 name);

//~ File System

MD_FUNCTION MD_String8  MD_LoadEntireFile(MD_String8 filename);
MD_FUNCTION MD_b32      MD_FileIterIncrement(MD_FileIter *it, MD_String8 path, MD_FileInfo *out_info);

#endif // MD_H

/*
Copyright 2021 Dion Systems LLC

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
