set(
    sources
    SignTx.cpp SignTx.h
    main.cpp chaincode.pb.h
    chaincode.pb.cc
)

# add_library(txsign ${sources})
add_executable(txsign ${sources})

target_link_libraries(
    txsign
    PUBLIC devcrypto ${PROTOBUF_LIBRARY}
)

install(TARGETS txsign DESTINATION bin)
