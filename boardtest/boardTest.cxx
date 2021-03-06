/*
 * Matfinder, a program to help chess engines to find mat
 *
 * Copyright© 2013 Philippe Virouleau
 *
 * You can contact me at firstname.lastname@imag.fr
 * (Replace "firstname" and "lastname" with my actual names)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <iostream>
#include <fstream>
#include <cstdint>
#include "Chessboard.h"
#include "Hashing.h"
#include "Utils.h"
#include "Options.h"

using namespace std;
using namespace Board;

int main()
{
    Options::setVerboseLevel(2);
    //string fen = "rnbqkbnr/pp2pppp/8/2ppP3/8/8/PPPP1PPP/RNBQKBNR w KQkq d6 0 3";
    string fenfen = "rnbqkbnr/pp1ppppp/8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R b KQkq - 1 2";
    string fen = "2r5/3P4/8/8/5K2/8/3k4/8 w - - 0 38";
    string fenInsuficient = "8/8/8/3k4/3b4/3K4/8/8 w - - 0 1";
    //Chessboard *test = Chessboard::createChessboard();
    Chessboard *test = Chessboard::createFromFEN(fen);
    uint64_t hash = HashTable::hashBoard(test);
    uint64_t hashFen = HashTable::hashFEN(fen);

    Utils::output(test->to_string() + "\n");
    Utils::output("Sufficient  : " + to_string(test->sufficientMaterial())
            + "\n");
    Utils::output("Hashs : \n");
    Utils::output("Board : " + to_string(hash) + "\n");
    Utils::output("FEN   : " + to_string(hashFen) + "\n");
    Utils::output("Fens : \n");
    Utils::output("Orig  : " + fen + "\n");
    Utils::output("Board : " + test->exportToFEN() + "\n");
    test->reInitFromFEN(fenfen);
    Utils::output(test->to_string() + "\n");
    Utils::output("Sufficient  : " + to_string(test->sufficientMaterial())
            + "\n");
    Utils::output("Fens : \n");
    Utils::output("Orig  : " + fenfen + "\n");
    Utils::output("Board : " + test->exportToFEN() + "\n");

    UCIMove mv = "e2e4n";
    Utils::output("e2e4n : " + to_string(Board::uciToPolyglot(mv)) + "\n");
    Utils::output("4892 : " + Board::polyglotToUci(4892) + "\n");
    Utils::output("\n");

    HashTable *tableTest = new HashTable();
    Node *node = new Node();
    node->pos = fen;
    MoveNode mn;
    mn.first = "f4f5";
    mn.second = NULL;
    node->legal_moves.push_back(mn);
    node->st = Node::DRAW;
    pair<uint64_t, Node *> p(HashTable::hashFEN(fen), node);
    tableTest->insert(p);

    Node *node2 = new Node();
    node2->pos = fen;
    mn.first = "e2e4";
    mn.second = NULL;
    node2->legal_moves.push_back(mn);
    node2->st = Node::MATE;
    pair<uint64_t, Node *> p2(HashTable::hashFEN(fenfen), node2);
    tableTest->insert(p2);

    Utils::output(tableTest->to_string() + "\n");

    Utils::output("Ouput to file\n");
    ofstream outputFile("oracleGardner.bin", ios::binary);
    tableTest->toPolyglot(outputFile);
    outputFile.close();

    test->reInitFromFEN(fenInsuficient);
    Utils::output(test->to_string() + "\n");
    Utils::output("Sufficient  : " + to_string(test->sufficientMaterial())
            + "\n");


    delete tableTest;


    Utils::output("Input from file\n");
    ifstream inputFile("oracleGardner.bin", ios::binary);
    HashTable *other = HashTable::fromPolyglot(inputFile);
    Utils::output("Table :\n");
    Utils::output(other->to_string() + "\n");
    delete other;
    inputFile.close();


    /*
     *test->uciApplyMove("e2e4");
     *test->uciApplyMove("e7e6");
     *test->uciApplyMove("d2d4");
     *test->uciApplyMove("d7d5");
     *test->uciApplyMove("e4d5");
     *test->uciApplyMove("e6d5");
     *test->uciApplyMove("g1f3");
     *test->uciApplyMove("g8f6");
     *test->uciApplyMove("f1e2");
     *test->uciApplyMove("c8e6");
     *test->uciApplyMove("e1g1");
     *test->uciApplyMove("b8c6");
     *test->uciApplyMove("f1e1");
     *Utils::output(test->to_string() + "\n");
     *const list<string> uciMoves = test->getUciMoves();
     *for (list<string>::const_iterator it = uciMoves.begin(), itEnd = uciMoves.end();
     *        it != itEnd; ++it)
     *    Utils::output((*it) + " ");
     *Utils::output("\n");
     */

    //test->uciApplyMove("f4e4");
    //test->uciApplyMove("d2c3");
    //test->uciApplyMove("d7d8q");
    //test->uciApplyMove("c8d8");
    //Utils::output(test->to_string() + "\n");
    //test->uciApplyMove("d2d3");
    //test->uciApplyMove("f4f5");
    //Utils::output(test->to_string() + "\n");

    /*
     *test->uciApplyMove("e2e4");
     *Utils::output(test->to_string() + "\n");
     *test->uciApplyMove("c7c5");
     *Utils::output(test->to_string() + "\n");
     *test->uciApplyMove("g1f3");
     *Utils::output(test->to_string() + "\n");
     */

    /*
     *list<string> movesToTry;
     *movesToTry.push_back("g1f3");
     *movesToTry.push_back("d7d6");
     *movesToTry.push_back("d2d4");
     *movesToTry.push_back("c5d4");
     *Utils::output("Trying a line :\n");
     */
    //Utils::output(test->tryUciMoves(movesToTry) + "\n");
    //Utils::output(test->to_string() + "\n");

    /*
     *test->uciApplyMove("d7d6");
     *Utils::output(test->to_string() + "\n");
     *test->uciApplyMove("d2d4");
     *Utils::output(test->to_string() + "\n");
     *test->uciApplyMove("c5d4");
     *Utils::output(test->to_string() + "\n");
     *test->uciApplyMove("f3d4");
     *Utils::output(test->to_string() + "\n");
     *test->uciApplyMove("g8f6");
     *Utils::output(test->to_string() + "\n");
     *test->uciApplyMove("b1c3");
     *Utils::output(test->to_string() + "\n");
     *test->uciApplyMove("g7g6");
     *Utils::output(test->to_string() + "\n");
     *test->uciApplyMove("c1e3");
     *Utils::output(test->to_string() + "\n");
     *test->uciApplyMove("f8g7");
     *Utils::output(test->to_string() + "\n");
     *test->uciApplyMove("f2f3");
     *Utils::output(test->to_string() + "\n");
     *test->uciApplyMove("e8g8");
     *Utils::output(test->to_string() + "\n");
     *test->uciApplyMove("d1d2");
     *Utils::output(test->to_string() + "\n");
     *test->uciApplyMove("b8c6");
     *Utils::output(test->to_string() + "\n");
     *test->uciApplyMove("e1c1");
     *Utils::output(test->to_string() + "\n");
     *const list<string> uciMoves = test->getUciMoves();
     *for (list<string>::const_iterator it = uciMoves.begin(), itEnd = uciMoves.end();
     *        it != itEnd; ++it)
     *    Utils::output((*it) + " ");
     *Utils::output("\n");
     */

    /*
     *test->undoMove();
     *Utils::output(test->to_string() + "\n");
     *test->undoMove();
     *Utils::output(test->to_string() + "\n");
     *test->undoMove();
     *Utils::output(test->to_string() + "\n");
     *test->undoMove();
     *Utils::output(test->to_string() + "\n");
     *test->undoMove();
     *Utils::output(test->to_string() + "\n");
     *test->undoMove();
     *Utils::output(test->to_string() + "\n");
     *test->undoMove();
     *Utils::output(test->to_string() + "\n");
     *test->undoMove();
     *Utils::output(test->to_string() + "\n");
     *test->undoMove();
     *Utils::output(test->to_string() + "\n");
     *test->undoMove();
     *Utils::output(test->to_string() + "\n");
     *test->undoMove();
     *Utils::output(test->to_string() + "\n");
     *test->undoMove();
     *Utils::output(test->to_string() + "\n");
     *test->undoMove();
     *Utils::output(test->to_string() + "\n");
     */
    //Utils::output(test->to_string() + "\n");
    //Utils::output(test->to_string() + "\n");
    delete test;
    return 0;
}
