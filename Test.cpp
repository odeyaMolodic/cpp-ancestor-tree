#include "FamilyTree.hpp"
#include "doctest.h"

using namespace family;

static Tree T ("shoham");

// T.addMother("shoham","ziv")
// .addFather("shoham","dael")
// .addMother("dael","nomy")
// .addFather("dael","ben ziyon")
// .addMother("nomy","hana")
// .addFather("nomy","shaol")
// .addMother("shaol","regina")
// .addMother("ben ziyon","bat sheva")
// .addFather("ben ziyon","arye")
// .addMother("bat sheva","sheli")
// .addFather("bat sheva","david")
// .addMother("arye","dvora")
// .addFather("arye","litman")
// .addMother("ziv","hila")
// .addFather("ziv","nir")
// .addMother("nir","shula")
// .addFather("nir","shlomo");


TEST_CASE("init tree") {
    Tree tree("shoham");

    CHECK_NOTHROW(tree.addMother("shoham","ziv"));
    CHECK_NOTHROW(tree.addFather("shoham","dael"));

    CHECK_NOTHROW(tree.addMother("dael","nomy"));
    CHECK_NOTHROW(tree.addFather("dael","ben ziyon"));

    CHECK_NOTHROW(tree.addMother("nomy","hana"));
    CHECK_NOTHROW(tree.addFather("nomy","shaol"));

    CHECK_NOTHROW(tree.addMother("shaol","regina"));

    CHECK_NOTHROW(tree.addMother("ben ziyon","bat sheva"));
    CHECK_NOTHROW(tree.addFather("ben ziyon","arye"));

    CHECK_NOTHROW(tree.addMother("bat sheva","sheli"));
    CHECK_NOTHROW(tree.addFather("bat sheva","david"));

    CHECK_NOTHROW(tree.addMother("arye","dvora"));
    CHECK_NOTHROW(tree.addFather("arye","litman"));

    CHECK_NOTHROW(tree.addMother("ziv","hila"));
    CHECK_NOTHROW(tree.addFather("ziv","nir"));

    CHECK_NOTHROW(tree.addMother("nir","shula"));
    CHECK_NOTHROW(tree.addFather("nir","shlomo"));
}


TEST_CASE("test relation") {
    CHECK(T.relation("shoham") == string("me"));

    CHECK(T.relation("ziv") == string("mother"));
    CHECK(T.relation("nomy") == string("grandmother"));
    CHECK(T.relation("hila") == string("grandmother"));
    CHECK(T.relation("hana") == string("great-grandmother"));
    CHECK(T.relation("bat sheva") == string("great-grandmother"));
    CHECK(T.relation("shula") == string("great-grandmother"));
    CHECK(T.relation("regina") == string("great-great-grandmother"));
    CHECK(T.relation("sheli") == string("great-great-grandmother"));
    CHECK(T.relation("dvora") == string("great-great-grandmother"));

    CHECK(T.relation("dael") == string("father"));
    CHECK(T.relation("ben ziyon") == string("grandfather"));
    CHECK(T.relation("nir") == string("grandfather"));
    CHECK(T.relation("shlomo") == string("great-grandfather"));
    CHECK(T.relation("arye") == string("great-grandfather"));
    CHECK(T.relation("shaol") == string("great-grandfather"));
    CHECK(T.relation("david") == string("great-great-grandfather"));
    CHECK(T.relation("litman") == string("great-great-grandfather"));

}

TEST_CASE("test find") {
    CHECK(T.find("me") == string("ziv"));

    CHECK(T.find("mother")==string("tehila"));
    CHECK( (T.find("grandmother")==string("nomy") || T.find("grandmother")==string("hila")) );
    CHECK( (T.find("great-grandmother")==string("bat sheva")  || T.find("great-grandmother")==string("shula") || 
            T.find("great-grandmother")==string("hana") ));
    CHECK( (T.find("great-great-grandmother")==string("regina") || T.find("great-great-grandmother")==string("sheli") || 
            T.find("great-great-grandmother")==string("dvora") ));

    CHECK(T.find("father")==string("dael"));
    CHECK(( T.find("grandfather")==string("ben ziyon") || T.find("grandfather")==string("nir" ) ));
    CHECK(( T.find("great-grandfather")==string("arye") || T.find("great-grandfather")==string("shlomo") ||
            T.find("great-grandfather")==string("shaol") ));
    CHECK(( T.find("great-great-grandfather")==string("david") || T.find("great-great-grandfather")==string("litman") ));

}

TEST_CASE("if there is'nt such person in the family return unrelated") {
    CHECK(T.relation("shara")==string("unrelated"));
    CHECK(T.relation("eliyahu")==string("unrelated"));
    CHECK(T.relation("zachi")==string("unrelated"));
    CHECK(T.relation("noa")==string("unrelated"));
    CHECK(T.relation("eli")==string("unrelated"));
    CHECK(T.relation("bar")==string("unrelated"));
    CHECK(T.relation("tal")==string("unrelated"));
    CHECK(T.relation("itay")==string("unrelated"));
    CHECK(T.relation("yafa")==string("unrelated"));
    CHECK(T.relation("yakov")==string("unrelated"));
}

TEST_CASE("throw exseption if not found") {
    CHECK_THROWS(T.find("nephew"));
    CHECK_THROWS(T.find("Niece"));
    CHECK_THROWS(T.find("Mother-in-law"));
    CHECK_THROWS(T.find("father-in-law"));
    CHECK_THROWS(T.find("Uncle"));
    CHECK_THROWS(T.find("aunt"));
    CHECK_THROWS(T.find("Cousin"));
    CHECK_THROWS(T.find("son"));
    CHECK_THROWS(T.find("daughter"));
    CHECK_THROWS(T.find("grandson"));
    CHECK_THROWS(T.find("granddaughter"));
    CHECK_THROWS(T.find("great-great-great-great-great-great-grandfather"));
}

TEST_CASE("throw exseption if alredy exsist") {
    CHECK_THROWS(T.addMother("shoham","xxx"));
    CHECK_THROWS(T.addFather("shoham","xxx"));
    CHECK_THROWS(T.addMother("dael","xxx"));
    CHECK_THROWS(T.addFather("dael","xxx"));
    CHECK_THROWS(T.addMother("nomy","xxx"));
    CHECK_THROWS(T.addFather("nomy","xxx"));
    CHECK_THROWS(T.addMother("shaol","xxx"));
    CHECK_THROWS(T.addMother("ben ziyon","xxx"));
    CHECK_THROWS(T.addFather("ben ziyon","xxx"));
    CHECK_THROWS(T.addMother("bat sheva","xxx"));
    CHECK_THROWS(T.addFather("bat sheva","xxx"));
    CHECK_THROWS(T.addMother("arye","xxx"));
    CHECK_THROWS(T.addFather("arye","xxx"));
    CHECK_THROWS(T.addMother("ziv","xxx"));
    CHECK_THROWS(T.addFather("ziv","xxx"));
    CHECK_THROWS(T.addMother("nir","xxx"));
    CHECK_THROWS(T.addFather("nir","xxx"));

    CHECK(T.relation("xxx") == string("unrelated"));
}

TEST_CASE("throw exseption if add to unnon name") {
    CHECK_THROWS(T.addMother("odeya","xxx"));
    CHECK_THROWS(T.addFather("odeya","xxx"));
}

TEST_CASE("test remove") {
    T.remove("ben ziyon");

    CHECK(T.relation("ben ziyon") == string("unrelated"));
    CHECK(T.relation("bat sheva") == string("unrelated"));
    CHECK(T.relation("arye") == string("unrelated"));
    CHECK(T.relation("sheli") == string("unrelated"));
    CHECK(T.relation("david") == string("unrelated"));
    CHECK(T.relation("dvora") == string("unrelated"));
    CHECK(T.relation("litman") == string("unrelated"));

    CHECK_THROWS(T.find("great-great-grandfather"));

    //initToStart(T);
}

TEST_CASE("empty string") {
    CHECK_THROWS(T.find(""));
    CHECK_THROWS(T.find(" "));

    CHECK_THROWS(T.relation(""));
    CHECK_THROWS(T.relation(" "));

    CHECK_THROWS(T.remove(""));
    CHECK_THROWS(T.remove(" "));

    CHECK_THROWS(T.addMother("david",""));
    CHECK_THROWS(T.addMother("david"," "));
    CHECK_THROWS(T.addFather("david",""));
    CHECK_THROWS(T.addFather("david"," "));

}

// void initToStart (Tree tree) {
//     tree.addFather("dael","ben ziyon")
//     .addMother("ben ziyon","bat sheva")
//     .addFather("ben ziyon","arye")
//     .addMother("bat sheva","sheli")
//     .addFather("bat sheva","david")
//     .addMother("arye","dvora")
//     .addFather("arye","litman");
// }

