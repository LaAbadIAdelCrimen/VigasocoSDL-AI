// ... existing code ...
// Reemplazar todas las ocurrencias de io_service con io_context
        SocketAdaptor(boost::asio::io_context& io_context, context*)
            : socket_(io_context)
        {
        }

        boost::asio::io_context& get_io_service()
        {
            return socket_.get_executor().context();
        }
// ... existing code ...