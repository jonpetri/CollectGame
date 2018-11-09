#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>


#include "model/item/items.h"


#include "model/item/item.h"
#include "model/game/gameparameters.h"
#include "model/node/node.h"
#include <iostream>
#include <string>


BOOST_AUTO_TEST_SUITE( item_suite )



BOOST_AUTO_TEST_CASE(ceateRandomItems)
{
    Items is;
    std::shared_ptr<GameParameters> p = std::make_shared<GameParameters>();
    p->setGridSideSize(10);
    p->setRatio_ItemCountVsNodeCount(1);
    is.ceateRandomItems(p);

    BOOST_CHECK_EQUAL(is.count(), p->itemCount());

    BOOST_CHECK(is.item(0) != nullptr);
    BOOST_CHECK(is.item(is.count()-1) != nullptr);
}

BOOST_AUTO_TEST_CASE(total_weight_value)
{
    Items is;
    std::shared_ptr<GameParameters> p = std::make_shared<GameParameters>();
    p->setGridSideSize(10);
    p->setRatio_ItemCountVsNodeCount(1);
    is.ceateRandomItems(p);

    int iTotalWeight = 0;
    int iTotalValue = 0;
    for (unsigned int i = 0 ; i < is.count() ; ++i)
    {
        iTotalWeight += is.item(i)->weight();
        iTotalValue += is.item(i)->value();
    }

    BOOST_CHECK_EQUAL(is.weight(), iTotalWeight);
    BOOST_CHECK_EQUAL(is.value(), iTotalValue);
}

BOOST_AUTO_TEST_CASE(getItemBatchOfHolder)
{

Items is;
Items node1ItemBatch;
Items node2ItemBatch;

std::shared_ptr<GameParameters> p = std::make_shared<GameParameters>();
std::shared_ptr<Node> n1 = Node::create();
std::shared_ptr<Node> n2 = Node::create();
    int iTotalWeightInNode1 = 0;
    int iItemCountOfNode1 = 0;
    int iTotalWeightInNode2 = 0;
    int iItemCountOfNode2 = 0;

p->setGridSideSize(10);
p->setRatio_ItemCountVsNodeCount(1);
is.ceateRandomItems(p);

  for (unsigned int i = 0 ; i < is.count()/2 ; ++i)
  {
      is.item(i)->setHolder(n1);
      iTotalWeightInNode1 += is.item(i)->weight();
      ++iItemCountOfNode1;
  }
  for (unsigned int i = is.count()/2 ; i < is.count() ; ++i)
  {
      is.item(i)->setHolder(n2);
      iTotalWeightInNode2 += is.item(i)->weight();
      ++iItemCountOfNode2;
  }

  is.getItemBatchOfHolder(n1,node1ItemBatch);
  BOOST_CHECK_EQUAL(node1ItemBatch.count(), iItemCountOfNode1);
  BOOST_CHECK_EQUAL(node1ItemBatch.weight(), iTotalWeightInNode1);
  for (unsigned int i = 0 ; i < node1ItemBatch.count() ; ++i)
      BOOST_CHECK_EQUAL(node1ItemBatch.item(i)->holder() , n1);

  is.getItemBatchOfHolder(n2,node2ItemBatch);
  BOOST_CHECK_EQUAL(node2ItemBatch.count(), iItemCountOfNode2);
  BOOST_CHECK_EQUAL(node2ItemBatch.weight(), iTotalWeightInNode2);
  for (unsigned int i = 0 ; i < node2ItemBatch.count() ; ++i)
      BOOST_CHECK_EQUAL(node2ItemBatch.item(i)->holder() , n2);
}

BOOST_AUTO_TEST_SUITE_END()
