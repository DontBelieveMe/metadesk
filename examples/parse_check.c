/* 
** Example: parse-check
**
 ** This example shows how to use the metadesk library to parse metadesk files,
** print errors, and dump verbose feedback on the resulting metadesk trees.
** This is also a nice utility for checking and inspecting your metadesk files.
**
*/

//~ Includes and globals //////////////////////////////////////////////////////

// @notes Print helpers will make it easier to print the errors. This brings in
//  C's stdio.h. It is possible to use error messages without print helpers,
//  but a dependency on stdio.h is fine here so we will use it.
#define MD_ENABLE_PRINT_HELPERS 1

#include "md.h"
#include "md.c"

// @notes For simple single-threaded memory management in a run-once-and-exit
//  utility, a single global arena is our prefered setup.
static MD_Arena *arena = 0;


//~ main //////////////////////////////////////////////////////////////////////

int main(int argument_count, char **arguments)
{
    // setup the global arena
    // @notes Metadesk arenas do linear reserve-and-commit allocation. This
    //  code makes an arena with a 1 terabyte reserve which works quite nicely,
    //  so long as we aren't doing more than a few of them. 
    arena = MD_ArenaAlloc(1ull << 40);
    
    
    // parse all files passed to the command line
    MD_Node *list = MD_MakeList(arena);
    for(int i = 1; i < argument_count; i += 1)
    {
        
        // parse the file
        // @notes Here we rely on MD_ParseWholeFile which loads the file itself
        //  and then does the whole parse. In a simple utility program like
        //  this metadesk's default implementations for the overrides make
        //  this work.
        MD_String8 file_name = MD_S8CString(arguments[i]);
        MD_ParseResult parse_result = MD_ParseWholeFile(arena, file_name);
        
        // print metadesk errors
        for (MD_Message *message = parse_result.errors.first;
             message != 0;
             message = message->next)
        {
            // @notes To print a message from the parse, technically we can do
            //  whatever we want. But we'll use the message format suggested
            //  by the metadesk library. First we get the code location - which
            //  means the file name and line number - for the node on this
            //  message. Then we pass the details of this message to the
            //  MD_PrintMessage helper function.
            MD_CodeLoc code_loc = MD_CodeLocFromNode(message->node);
            MD_PrintMessage(stdout, code_loc, message->kind, message->string);
        }
        
        // save to parse results list
        // @notes Metadesk message kinds are sorted in order of severity. So we
        //  can easily check the severity of a entire parse by looking at the
        //  `max_message_kind` field on the errors from the parse result. Here
        //  only push the parse result onto our list if there were no errors.
        if (parse_result.errors.max_message_kind >= MD_MessageKind_Error)
        {
            MD_PushNewReference(arena, list, parse_result.node);
        }
    }
    
    // print the verbose parse results
    for(MD_EachNodeRef(root, list->first_child))
    {
        for(MD_EachNode(node, root->first_child))
        {
            MD_String8List strs =
                MD_DebugStringListFromNode(arena, node, 0, MD_S8Lit(" "), MD_GenerateFlags_Tree);
            MD_String8 str = MD_S8ListJoin(arena, strs, 0);
            fwrite(str.str, str.size, 1, stdout);
            fwrite("\n", 1, 1, stdout);
        }
    }
    
    return 0;
}
