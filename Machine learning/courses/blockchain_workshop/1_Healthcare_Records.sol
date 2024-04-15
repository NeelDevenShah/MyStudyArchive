// SPDX-License-Identifier: MIT
pragma solidity ^0.8.9;

contract HealthcareRecords {

    // Struct to represent a patient's medical record
    struct MedicalRecord {
        string patientName;
        uint256 birthDate;
        string diagnosis;
        string treatment;
        address healthcareProvider;
        bool isApproved;
    }

    // Mapping to store medical records with patient addresses as keys
    mapping(address => MedicalRecord) public medicalRecords;

    // Event emitted when a new medical record is added
    event MedicalRecordAdded(address indexed patient, string diagnosis, string treatment, address healthcareProvider);

    // Modifier to restrict access to only approved healthcare providers
    modifier onlyApprovedProvider() {
        require(isApprovedProvider(msg.sender), "Only approved healthcare providers can access this function.");
        _;
    }

    // Mapping to store approved healthcare providers
    mapping(address => bool) public approvedProviders;

    // Function to add a new medical record to the blockchain
    function addMedicalRecord(
        address _patient,
        string memory _patientName,
        uint256 _birthDate,
        string memory _diagnosis,
        string memory _treatment
    ) public onlyApprovedProvider {

        // Ensure the patient's medical record doesn't already exist
        require(medicalRecords[_patient].healthcareProvider == address(0), "Medical record for this patient already exists.");

        // Create a new MedicalRecord struct
        MedicalRecord memory newRecord = MedicalRecord({
            patientName: _patientName,
            birthDate: _birthDate,
            diagnosis: _diagnosis,
            treatment: _treatment,
            healthcareProvider: msg.sender,
            isApproved: true
        });

        // Store the medical record in the mapping
        medicalRecords[_patient] = newRecord;

        // Emit the event
        emit MedicalRecordAdded(_patient, _diagnosis, _treatment, msg.sender);
    }

    // Function to grant approval to a healthcare provider
    function approveHealthcareProvider(address _provider) public {
        require(msg.sender == owner, "Only the contract owner can approve healthcare providers.");
        approvedProviders[_provider] = true;
    }

    // Function to check if an address is an approved healthcare provider
    function isApprovedProvider(address _provider) public view returns (bool) {
        return approvedProviders[_provider];
    }

    // Contract owner
    address public owner;

    // Contract constructor
    constructor() {
        owner = msg.sender;
    }
}
