// SPDX-License-Identifier: Apache-2.0

// Solidity version to be used for compilation
pragma solidity ^0.8.9;

// LandRegistry contract that simulates a basic land registry system
contract LandRegistry {

    // Struct to represent a land parcel
    struct Land {
        address payable owner;  // Owner's Ethereum address (payable for transactions)
        string location;        // Geographical location of the land parcel
        string parcelID;        // Unique identifier for the land parcel
        uint256 price;          // Price of the land parcel in wei
    }

    // Mapping to store information about registered land parcels
    mapping (string => Land) public lands;

    // Event emitted when a new land parcel is registered
    event LandRegistered(
        address indexed owner,
        string parcelID
    );

    // Event emitted when ownership of a land parcel is transferred
    event LandTransferred(
        address indexed oldOwner,
        address indexed newOwner,
        string parcelID
    );

    // Modifier to restrict access to only the current owner of a land parcel
    modifier onlyLandOwner(string memory _parcelID) {
        require(
            lands[_parcelID].owner == msg.sender,
            "Only the current owner can perform this operation."
        );
        _;
    }

    // Function to register a new land parcel
    function registerLand(
        string memory _location,
        string memory _parcelID,
        uint256 _price
    ) public {

        // Check if the land parcel is already registered
        require(
            lands[_parcelID].owner == address(0),
            "This land parcel is already registered."
        );

        // Create a new Land struct and store it in the lands mapping
        lands[_parcelID] = Land(
            payable(msg.sender),
            _location,
            _parcelID,
            _price
        );

        // Emit the event to notify about the registration
        emit LandRegistered(
            msg.sender,
            _parcelID
        );
    }

    // Function to sell/transfer ownership of a land parcel to a new owner
    function sellLand(
        address payable _buyer,
        string memory _parcelID
    ) public onlyLandOwner(_parcelID) {
        // Transfer the land to the new owner
        address oldOwner = lands[_parcelID].owner;
        lands[_parcelID].owner = _buyer;

        // Emit the event to notify about the ownership transfer
        emit LandTransferred(oldOwner, _buyer, _parcelID);
    }

    // Function to verify details of a land parcel
    function verifyLand(
        string memory _parcelID
    ) public view returns (
        address,
        string memory,
        string memory,
        uint256
    ) {
        // Check if the land parcel is registered
        require(
            lands[_parcelID].owner != address(0),
            "This land parcel is not registered."
        );

        // Return the details of the land parcel
        return (
            lands[_parcelID].owner,
            lands[_parcelID].location,
            lands[_parcelID].parcelID,
            lands[_parcelID].price
        );
    }
}
