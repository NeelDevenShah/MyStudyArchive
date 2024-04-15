// SPDX-License-Identifier: MIT
pragma solidity ^0.8.9;

contract SupplyChain {

    // Struct to represent a product in the supply chain
    struct Product {
        uint productId;
        string productName;
        address producer;
        address distributor;
        address retailer;
        address consumer;
        bool isSold;
    }

    // Mapping to store products with their unique IDs
    mapping(uint => Product) public products;

    // Counter to generate unique product IDs
    uint public productCounter;

    // Event emitted when a new product is added to the supply chain
    event ProductAdded(uint productId, string productName, address producer);

    // Event emitted when a product is sold to a distributor
    event ProductSold(uint productId, string productName, address seller, address buyer);

    // Function to add a new product to the supply chain
    function addProduct(string memory _productName) public {
        productCounter++;
        Product memory newProduct = Product({
            productId: productCounter,
            productName: _productName,
            producer: msg.sender,
            distributor: address(0),
            retailer: address(0),
            consumer: address(0),
            isSold: false
        });

        products[productCounter] = newProduct;

        emit ProductAdded(productCounter, _productName, msg.sender);
    }

    // Function to sell a product to a distributor
    function sellToDistributor(uint _productId, address _distributor) public {
        require(products[_productId].producer == msg.sender, "Only the producer can sell the product.");
        require(!products[_productId].isSold, "Product is already sold.");

        products[_productId].distributor = _distributor;
        products[_productId].isSold = true;

        emit ProductSold(_productId, products[_productId].productName, msg.sender, _distributor);
    }

    // Function to sell a product to a retailer
    function sellToRetailer(uint _productId, address _retailer) public {
        // Allow the retailer to sell the product directly to the consumer
        // Commenting out the distributor check
        // require(products[_productId].distributor == msg.sender, "Only the distributor can sell the product.");
        require(!products[_productId].isSold, "Product is already sold.");

        products[_productId].retailer = _retailer;
        products[_productId].isSold = true;

        emit ProductSold(_productId, products[_productId].productName, msg.sender, _retailer);
    }

    // Function to sell a product to a consumer
    function sellToConsumer(uint _productId, address _consumer) public {
        // require(products[_productId].retailer == msg.sender, "Only the retailer can sell the product.");
        require(!products[_productId].isSold, "Product is already sold.");

        products[_productId].consumer = _consumer;
        products[_productId].isSold = true;

        emit ProductSold(_productId, products[_productId].productName, msg.sender, _consumer);
    }
}
