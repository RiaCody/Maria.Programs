#include "splashkit.h"
#include <string>
#include <vector>
using std::vector;
using namespace std;

struct knight_data
{
    string name, birth_month, quests;
    int age;
    vector<string> tools;
};

struct kingdom_data
{
    string name;
    vector<knight_data> knights;
};

enum knight_update_option
{
    UPDATE_NAME,
    UPDATE_AGE,
    UPDATE_BIRTH_MONTH,
    UPDATE_QUESTS,
    ADD_TOOLS,
    REMOVE_TOOL,
    FINISH_UPDATE

};

enum system_actions_menu
{
    ADD_KNIGHT,
    DELETE_KNIGHT,
    QUERY_KNIGHT,
    UPDATE_KNIGHT,
    DISPLAY_KNIGHT,
    FINISH_SYSTEM_ACTION,
};

enum update_tool
{
    CHANGE_TOOL,
    END_UPDATE,
};
string read_string(string prompt)
{
    string result;
    write(prompt);
    result = read_line();
    return result;
}

int read_integer(string prompt)
{
    string line;
    line = (read_string(prompt));
    return convert_to_integer(line);
}

knight_update_option read_knight_update_option()
{
    int result;

    write_line("1: Update Name..");
    write_line("2: Update Age..");
    write_line("3: Update Birth Month..");
    write_line("4: Add a quest..");
    write_line("5: Update a Tool..");
    write_line("6: Delete a Tool..");
    write_line("7: Finish Update..");

    result = read_integer("Select Option: ");

    return static_cast<knight_update_option>(result - 1);
}

knight_data read_knight()
{
    knight_data result;

    result.name = read_string("Enter name: ");
    result.age = read_integer("What is your age: ");
    result.birth_month = read_string("What is your birth month: ");
    result.quests = read_string("what quest do you want to add to the knight: ");
    result.tools.push_back(read_string("Enter Tools: "));

    return result;
}

void update_name(kingdom_data &kingdom)
{
    int result, i;

    result = read_integer("which knights name will you change: ");
    i = result - 1;

    kingdom.knights[i].name = read_string("Enter new  name: ");
}

void update_age(kingdom_data &kingdom)
{
    int result, i;

    result = read_integer("which knights age will you change: ");
    i = result - 1;

    kingdom.knights[i].age = read_integer("Enter new age: ");
}

void update_birth_month(kingdom_data &kingdom)
{
    int result, i;

    result = read_integer("which knights birth month will you change: ");
    i = result - 1;

    kingdom.knights[i].birth_month = read_string("Enter new birth month: ");
}

void update_quest(kingdom_data &kingdom)
{
    int result, i;

    result = read_integer("which knights quest  will you change: ");
    i = result - 1;

    kingdom.knights[i].quests = read_string("Knight new challagne added: ");
}

void write_knight(const knight_data &knight)
{
    write_line(knight.name + " AGE: " + to_string(knight.age) + " MONTH: " + knight.birth_month + " QUEST:" + knight.quests + " TOOLS IN KNIGHT BAG:");

    for (int i = 0; i < knight.tools.size(); i++)

    {

        write_line(to_uppercase(knight.tools[i]));
    }
}

void write_kingdom(const kingdom_data &kingdom)
{
    write_line("        == = = =KINGDOM= = == ==");
    write_line("");
    write_line( "               " + kingdom.name);

    for (int i = 0; i < kingdom.knights.size(); i++)

    {

        write("Knight " + to_string(i + 1) + ": ");

        write_knight(kingdom.knights[i]);
    }

    write_line("        == === == == == == == ===");
}

kingdom_data read_kingdom()
{
    kingdom_data result;

    result.name = read_string("Enter kingdom name: ");

    return result;
}

void add_knight(kingdom_data &kingdom)
{
    knight_data new_knight;

    new_knight = read_knight();

    kingdom.knights.push_back(new_knight);
}

void remove_knight(kingdom_data &kingdom, int index)
{

    if (index >= 0 and index < kingdom.knights.size())

    {

        int last_idx;

        last_idx = kingdom.knights.size() - 1;

        kingdom.knights[index] = kingdom.knights[last_idx];

        kingdom.knights.pop_back();
    }
}

int select_knight(const kingdom_data &kingdom)
{
    write_kingdom(kingdom);
    int i = -1;

    while (i < 1 or i > kingdom.knights.size())

    {

        i = read_integer("Please Select a Knight: ");

        if (i < 1 or i > kingdom.knights.size())

        {

            write_line("Invalid Option Please Try Again!");
        }
    }

    return i - 1;
}

void query_knight(kingdom_data &kingdom)
{
    int index_knights = select_knight(kingdom);
    write_knight(kingdom.knights[index_knights]);
}

void tool_information(const knight_data &knight)
{
    write_line("tools information: ");

    for (int i = 0; i < knight.tools.size(); i++)

    {

        write_line(to_uppercase(to_string(i + 1)) + ". " + knight.tools[i]);
    }
}

void query_knight(const kingdom_data &kingdom)
{
    int select;
    write_line();
    write_line("******** Update Knight ********");

    for (int i = 0; i < kingdom.knights.size(); i++)

    {

        write("Knight " + to_string(i + 1) + ": ");

        write_knight(kingdom.knights[i]);
    }

    select = select_knight(kingdom);

    write_line("Knight " + to_string(select + 1) + ": ");

    write_knight(kingdom.knights[select]);

    tool_information(kingdom.knights[select]);
}

void update_tools(kingdom_data &kingdom)
{
    int result, i;

    write_line("============================");

    result = read_integer("Which knights tool will you change: ");

    write_line("============================");

    i = result - 1;

    write_line("============================");

    kingdom.knights[i].tools.push_back(to_uppercase((read_string("Tool to add: "))));

    write_line("============================");
}

void delete_knight_kingdom(kingdom_data &kingdom)
{

    int i = select_knight(kingdom);
    remove_knight(kingdom, i);
}

void delete_tool(kingdom_data &kingdom)
{
    int i;
    int knight;

    knight = read_integer("which Knight will you remove a tool from: ");

    i = knight - 1;

    tool_information(kingdom.knights[i]);

    int index = read_integer("Please select a tool: ");
    index = index - 1;

    if (index >= 0 and index < kingdom.knights[i].tools.size())

    {
        int last_idx;

        last_idx = kingdom.knights[i].tools.size() - 1;

        kingdom.knights[i].tools[index] = kingdom.knights[i].tools[last_idx];

        kingdom.knights[i].tools.pop_back();
    }
}

void delete_tool_knight(kingdom_data &kingdom)
{
    delete_tool(kingdom);
}

system_actions_menu kingdom_data_update_option()
{

    int result;

    write_line("        1: ADD KNIGHT");
    write_line("        2: DELETE KNIGHT");
    write_line("        3: QUERY KNIGHT");
    write_line("        4: UPDATE KNIGHTS");
    write_line("        5: DISPLAY KNIGHTS");
    write_line("        6: FINISH SYSTEM ACTION");

    result = read_integer("     Select Option: ");

    return static_cast<system_actions_menu>(result - 1);
}

void update_knight(kingdom_data &kingdom)
{
    knight_update_option option;

    do

    {

        write_line();

        write_line("            **** UPDATE KNIGHT ****");

        for (int i = 0; i < kingdom.knights.size(); i++)

        {

            write("KNIGHT[" + to_string(i + 1) + "]: ");

            write_knight(kingdom.knights[i]);
        }

        write_line();

        option = read_knight_update_option();

        switch (option)

        {

        case UPDATE_NAME:
            update_name(kingdom);
            break;

        case UPDATE_AGE:
            update_age(kingdom);
            break;

        case UPDATE_BIRTH_MONTH:
            update_birth_month(kingdom);
            break;

        case UPDATE_QUESTS:
            update_quest(kingdom);
            break;

        case ADD_TOOLS:
            update_tools(kingdom);
            break;

        case REMOVE_TOOL:
            delete_tool_knight(kingdom);
            break;

        case FINISH_UPDATE:
            break;

        default:

            write_line("Please select a valid option!");
        }

    } while (option != FINISH_UPDATE);
}

void update_kingdom(kingdom_data &kingdom)
{
    system_actions_menu option;

    do

    {

        write_line();
        write_line("  =   =   =  KINGDOM DEATILS =    =   =      ");

        write_kingdom(kingdom);
        option = kingdom_data_update_option();

        switch (option)

        {

        case ADD_KNIGHT:
            int many;
            many= read_integer("how many knights do you wish to add: ");

            while (many <= 0)
            {
                write_line("Please eneter a valid number!");
                many = read_integer("how many knights do you wish to add: ");
            }

            while (many > 0)
            {
                many = many - 1;
                add_knight(kingdom);
            }

            write_kingdom(kingdom);
            break;
        case DELETE_KNIGHT:
            if (kingdom.knights.size() > 0)

                delete_knight_kingdom(kingdom);

            else
                write_line("No knights found in database!");
            break;
        case QUERY_KNIGHT:
            if

                (kingdom.knights.size() > 0)

                query_knight(kingdom);

            else
                write_line(" No knights found in database!");
            break;
        case UPDATE_KNIGHT:
            if (kingdom.knights.size() > 0)

                update_knight(kingdom);

            else
                write_line("No knights found in database!");

        case DISPLAY_KNIGHT:
            write_kingdom(kingdom);
            break;
        case FINISH_SYSTEM_ACTION:
            write_line("THANKS FOR VISTING !!");
            break;

        default:

            write_line("no valid option selected!");
        }

    } while (option != FINISH_SYSTEM_ACTION);
}

int main()
{
    kingdom_data my_kingdom = read_kingdom();
    write_kingdom(my_kingdom);
    update_kingdom(my_kingdom);

    return 0;
}