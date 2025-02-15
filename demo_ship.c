
#include <stdio.h>
#include <stdlib.h>
#include <string.h>     /* for memcpy */
#include <strings.h>    /* for strcasecmp */
#include <time.h>

#include "warpwar_crt.h"
#include "warpwar_ship.h"
#include "warpwar_combat.h"

int main (int argc, char **argv)
{
    struct warpwar_ship_t *ptr_ship1;
    struct warpwar_ship_t *ptr_ship2;
    struct warpwar_ship_t *ptr_ship3;
    warpwar_bool_t isa_warpship = 1;
    warpwar_bool_t verbose = 0;
    unsigned int idnum = 1;
    unsigned int pd, b, s, t, m, sr;
    unsigned int credits_in_bank_blue = 10000;
    unsigned int credits_in_bank_white = 10000;
    warpwar_ship_stats_t   orders;
    int result;
    int rval;
    int be_verbose;

    srandom(time(0));

    /* ship 1: */
    ptr_ship1 = warpwar_ship_build(isa_warpship = 1, ALLEGIANCE_BLUE,
        pd = 13, b = 6, s = 6, t = 0, m = 0, sr = 0,
        &credits_in_bank_blue, verbose);
    /* ship 2: */
    ptr_ship2 = warpwar_ship_build(isa_warpship = 1, ALLEGIANCE_WHITE,
        pd = 10, b = 8, s = 7, t = 0, m = 0, sr = 0,
        &credits_in_bank_white, verbose);
    ptr_ship2 = warpwar_ship_build(isa_warpship = 0, ALLEGIANCE_BLUE,
        pd = 2, b = 0, s = 0, t = 1, m = 6, sr = 0,
        &credits_in_bank_blue, verbose);
    warpwar_print_all_ships();

    /* have ship id=1 attack ship id=2 with its beam */
    memset(&orders, 0, sizeof(orders));
    orders.pd = 1;
    orders.b  = 6;
    orders.s  = 6;
    rval = warpwar_ship_issue_orders(1, 2, TACTIC_ATTACK, &orders, 1);
    if (rval < 0)
    {
        printf("warpwar_ship_issue_orders returned %d\n", rval);
    }

    /* have ship id=2 attack ship id=1 with its beam */
    memset(&orders, 0, sizeof(orders));
    orders.pd = 2;
    orders.b  = 8;
    orders.s  = 0;
    rval = warpwar_ship_issue_orders(2, 1, TACTIC_ATTACK, &orders, 1);
    if (rval < 0)
    {
        printf("warpwar_ship_issue_orders returned %d\n", rval);
    }

    warpwar_resolve_all_attacks();
    warpwar_resolve_all_ships_damages();
    warpwar_print_all_ships();

    /* have ship id=1 attack ship id=2 with its beam */
    memset(&orders, 0, sizeof(orders));
    orders.pd = 1;
    orders.b  = 3;
    orders.s  = 1;
    rval = warpwar_ship_issue_orders(1, 2, TACTIC_ATTACK, &orders, 1);
    if (rval < 0)
    {
        printf("warpwar_ship_issue_orders returned %d\n", rval);
    }

    /* have ship id=2 attack ship id=1 with its beam */
    memset(&orders, 0, sizeof(orders));
    orders.pd = 1;
    orders.b  = 5;
    orders.s  = 0;
    rval = warpwar_ship_issue_orders(2, 1, TACTIC_DODGE, &orders, 1);
    if (rval < 0)
    {
        printf("warpwar_ship_issue_orders returned %d\n", rval);
    }

    warpwar_resolve_all_attacks();
    warpwar_resolve_all_ships_damages();
    warpwar_print_all_ships();

    warpwar_ship_decommission(ptr_ship1);
    warpwar_ship_decommission(ptr_ship2);
    warpwar_ship_decommission(ptr_ship3);
    return 0;
}

