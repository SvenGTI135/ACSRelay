/*
 Copyright 2015 Victor Nicolae.

 This file is part of ACSRelay.

 ACSRelay is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 ACSRelay is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with ACSRelay.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _log_h
#define _log_h

#include <fstream>
#include <string.h>
#include <locale>

/**
 * @class Log
 * @brief Used to output log messages to screen and the log file.
 */
class Log
{
private:
    /**
     * @class _log_manip
     * @brief Internal class used by the Log class to output varios data.
     */
    template <class T1, class T2>
    class _log_manip
    {
    public:
        /**
         * @brief _log_manip constructor
         * @param fp Pointer to the function that will output data.
         * @param arg1 First argument that will be piped to the function.
         * @param arg2 Second argument that will be piped to the function.
         */
        _log_manip (std::string (*fp) (T1 arg1, T2 arg2), T1 arg1, T2 arg2);
        /**
         * @brief Calls the function that outputs data.
         * @return A string object, as generated by the function.
         */
        std::string _call () const { return pf ( _arg1, _arg2 ); }
    private:
        std::string (*pf) (T1 arg1, T2 arg2);
        T1 _arg1;
        T2 _arg2;
    };
    
public:

#ifndef NO_WSTRING
    /**
     * @brief std::codecvt implementation with a public destructor.
     */
    template <class internT, class externT, class stateT>
    struct codecvt : std::codecvt<internT,externT,stateT>
    { ~codecvt(){} };

    /**
     * @brief Used to convert from UTF-16 to standard char.
     */
    typedef std::wstring_convert<codecvt<char16_t,char,std::mbstate_t>,char16_t> convert16;
    /**
     * @brief Used to convert from UTF-32 to standard char.
     */
    typedef std::wstring_convert<codecvt<char32_t,char,std::mbstate_t>,char32_t> convert32;
#endif
    
    /**
     * @brief Possible levels of verbosity for the log functions.
     * Lower values have a higher priority. For example, if a message with
     * a higher priority (lower enum value) than the logger output level is sent
     * the message will be printed. If it has a lower priority than the current
     * logger output level, it will be ignored.
     */
    enum OutputLevel
    {
        ERROR_LVL = 0, ///< Output level corresponding to error messages.
        WARNING_LVL = 1, ///< Output level corresponding to warning messages.
        NORMAL_LVL = 2, ///< Output level corresponding to usual informative messages.
        VERBOSE_LVL = 3, ///< Output level corresponding to more verbose messages.
        DEBUG_LVL = 4/*!< Output level corresponding to debug messages. If the output
                           level is set to this, all types of messages will be printed. */
    };

    /**
     * @brief Used to retrieve an instance to the Log instance.
     * @return The only constructed Log object in existence... ever.
     */
    static Log& GetLogger ()
    {
        static Log instance;
        return instance;
    }

    /**
     * @brief Used to get the current output level of the logger.
     * @return Log::OutputLevel value of the corresponding level.
     */
    static OutputLevel GetOutputLevel () { return GetLogger().mLevel; }

    /**
     * @brief Used to output debugging messages.
     * @return Log object ready to output debugging messages.
     */
    static Log& d ();
    /**
     * @brief Used to output error messages.
     * @return Log object ready to output error messages.
     */
    static Log& e ();
    /**
     * @brief Used to output general information messages.
     * @return Log object ready to output general information messages.
     */
    static Log& i ();
    /**
     * @brief Used to output more verbose messages.
     * @return Log object ready to output more verbose messages.
     */
    static Log& v ();
    /**
     * @brief Used to output warning messages.
     * @return Log object ready to output warning messages.
     */
    static Log& w ();

    /**
     * @brief Used to output characters to the log.
     * @param log Character to output in the log.
     * @return Log object that was used to perform the task.
     */
    Log& operator<< ( const char &log );
    /**
     * @brief Used to output strings to the log.
     * @param log String to output in the log.
     * @return Log object that was used to perform the task.
     */
    Log& operator<< ( const std::string &log );
    /**
     * @brief Used to output character arrays to the log.
     * This calls the string output operator.
     * @param log Character array to output in the log.
     * @return Log object that was used to perform the task.
     */
    Log& operator<< ( const char *log ) { return *this << ( std::string ( log ) ); }

    /**
     * @brief Used to output long integers to the log.
     * @param log Long integer to output in the log.
     * @return Log object that was used to perform the task.
     */
    Log& operator<< ( const long &log );
    /**
     * @brief Used to output integers to the log.
     * This calls the long integer output operator.
     * @param log Integer to output in the log.
     * @return Log object that was used to perform the task.
     */
    Log& operator<< ( const int &log ) { return *this << static_cast<long>(log); }
    /**
     * @brief Used to output short integers to the log.
     * This calls the long integer output operator.
     * @param log Short nteger to output in the log.
     * @return Log object that was used to perform the task.
     */
    Log& operator<< ( const short &log ) { return *this << static_cast<long>(log); }

    /**
     * @brief Used to output unsigned long integers to the log.
     * @param log Unsigned long integer to output in the log.
     * @return Log object that was used to perform the task.
     */
    Log& operator<< ( const unsigned long &log );
    /**
     * @brief Used to output unsigned integers to the log.
     * This calls the unsigned long integer output operator.
     * @param log Unsigned integer to output in the log.
     * @return Log object that was used to perform the task.
     */
    Log& operator<< ( const unsigned int &log ) { return *this << static_cast<unsigned long>(log); }
    /**
     * @brief Used to output unsigned short integers to the log.
     * This calls the unsigned long integer output operator.
     * @param log Unsigned short integer to output in the log.
     * @return Log object that was used to perform the task.
     */
    Log& operator<< ( const unsigned short &log ) { return *this << static_cast<unsigned long>(log); }

    /**
     * @brief Used to output floating point numbers to the log.
     * @param log Double floating point number to output in the log.
     * @return Log object that was used to perform the task.
     */
    Log& operator<< ( const double &log );
    /**
     * @brief Used to output boolean values to the log.
     * This outputs "TRUE" or "FALSE" depending on the parameter value.
     * @param log Boolean value to output in the log.
     * @return Log object that was used to perform the task.
     */
    Log& operator<< ( const bool &log );

    /**
     * @brief Used to output various data to the log.
     * @param manip Manipulator that is being used to retrieve the data.
     * @return Log object that was used to perform the task.
     */
    template<class T1, class T2>
    Log& operator << ( const _log_manip<T1, T2> &manip );

    /**
     * @brief Used to output ACSP packet data via a manipulator.
     * @param msg Packet data as a byte array.
     * @param len Packet size (equal to the byte array's size).
     * @return Manipulator object that will be used by the Log.
     */
    static _log_manip<char*, long> Packet ( char* msg, long len );
    /**
     * @brief Used to set the output level of the logger.
     * This must be called before logging any data, otherwise
     * it will have no effect whatsoever. As the Log does not
     * support switching from one output level to another on-the-fly.
     * @param level Desired output level.
     */
    static void SetOutputLevel ( const enum OutputLevel level );
    /**
     * @brief Used to change the log file.
     * This must be called before logging any data, otherwise
     * it will have no effect whatsoever. As the Log does not
     * support switching from one log file to another on-the-fly,
     * the first log file that is opened is the one that will be
     * used for the rest of the execution.
     * @param fn Path to the new log file name.
     */
    static void SetOutputFile ( const std::string fn );
    
private:
    Log ();

    /**
     * @brief Reads a UTF-32 string from a byte array.
     * @param s Pointer to a byte array.
     * @param n Number of UTF-32 characters to read (each UTF-32 has 4 bytes).
     * @return A standard string object.
     */
    static std::string ReadUTF32 ( char* s, int n );

    /**
     * @brief The default verbosity of the log functions.
     */
    static enum OutputLevel _log_level;
    /**
     * @brief The initial filename of the log file.
     */
    static std::string _log_file;

    // SINGLETON:

    Log (Log const&) = delete;
    void operator=(Log const&) = delete;

    template<class T1, class T2>
    friend class _log_manip;

    static std::string _log_packet ( char* msg, long len );
    
    std::ostream *mOutput;
    std::ofstream *mLogFile;
    
    enum OutputLevel mLevel;
    enum OutputLevel mRequestedLevel;
    
    std::string mLogFilename;
    bool mFileOutputEnabled;
    
    bool mTreatWarningsAsErrors;
};

#endif // _log_h
