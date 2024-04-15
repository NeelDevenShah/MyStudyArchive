// SPDX-License-Identifier: MIT
pragma solidity ^0.8.9;

contract Lottery {
    address public owner;             // Address of the contract owner
    address payable[] public players; // Array to store addresses of players
    address public winner;            // Address of the winner

    constructor() {
        owner = msg.sender; // Set the contract owner to the address that deploys the contract
    }

    // Modifier to ensure that only the owner can execute certain functions
    modifier onlyOwner() {
        require(msg.sender == owner, "Only the owner can call this function");
        _;
    }

    // Function for players to enter the lottery by sending 1 ether
    function enter() public payable {
        require(msg.value == 1 ether, "Must send exactly 1 ether to enter");
        players.push(payable(msg.sender)); // Add the player's address to the players array
    }

    // Function to generate a random number based on block information and player addresses
    function random() public view returns (uint8) {
        return
            uint8(
                uint256(
                    keccak256(
                        abi.encodePacked(
                            block.timestamp,
                            block.difficulty,
                            players
                        )
                    )
                ) % 251
            );
    }

    // Function for the owner to pick a winner using a random number
    function pickWinner() public onlyOwner {
        uint256 index = random() % players.length; // Pick a random index from the players array

        // Transfer the contract balance to the winner
        players[index].transfer(address(this).balance);
        winner = players[index]; // Set the winner's address

        // Reset the state of the contract by creating a new empty players array
        players = new address payable[](0);
    }
}
