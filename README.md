# Image Processor by AI

This project is designed to handle real-time streaming data, process it asynchronously using multiple algorithms, and send the processed data to RabbitMQ while maintaining data order and optimizing for high-frequency data handling.

## Features
- Real-time data streaming
- Data splitting into views
- Asynchronous processing with multiple algorithms
- RabbitMQ integration for processed data
- High-performance and order-preserving design

## Getting Started
1. Clone the repository.
2. Navigate to the `source` directory.
3. Compile and run the `main.cpp` program to initialize the processor.

```bash
g++ main.cpp -o ImageProcessor
./ImageProcessor
```

## Future Enhancements
- Add support for dynamic algorithm registration.
- Implement monitoring and logging for better observability.

## License
This project is licensed under the MIT License.
